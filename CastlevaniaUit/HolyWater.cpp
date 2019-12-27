#include"HolyWater.h"
#include"EffectDatabase.h"
#include"Simon.h"
CHolyWater::CHolyWater()
{
	LPANIMATION ani = new CAnimation(100);
	ani->Add(WEAPON, 21);
	animations[NORMAL_LEFT] = ani;

	ani = new CAnimation(100);
	ani->Add(WEAPON, 22);
	ani->Add(WEAPON, 23);
	animations[BURN_LEFT] = ani;

	ani = new CAnimation(100);
	ani->Add(WEAPON, 24);
	animations[NORMAL_RIGHT] = ani;

	ani = new CAnimation(100);
	ani->Add(WEAPON, 25);
	ani->Add(WEAPON, 26);
	animations[BURN_RIGHT] = ani;

	vy = -0.3;
	this->WeaponType = HOLYWATER;
	Currentstate = 0;
	this->IsDead = false;
	
}


void CHolyWater::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects)
{
	if (this->IsDead == false)
	{
		CGameObject::Update(dt);
		if (this->Currentstate == 0)
		{
			vx = nx * 0.3;
			vy += GAME_GRAVITY * dt;
		}
		else
		{
			vx = 0;
			vy = 0;
		}
		if (GetTickCount() - LifeTime >= 2000 && LifeTime != 0 &&Currentstate==1)
		{
			this->IsDead = true;
			LifeTime = 0;
		}

		if (this->Currentstate == 1)
		{
			if (nx > 0)
			{
				animation = animations[BURN_RIGHT];
			}
			else
			{
				animation = animations[BURN_LEFT];

			}
		}

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		CalcPotentialCollisions(colliable_objects, coEvents);

		if (coEvents.size() == 0)
		{

			x += dx;
			y += dy;


			for (UINT i = 0; i < colliable_objects->size(); i++)
			{
				if (isContain(this->GetBBox(), colliable_objects->at(i)->GetBBox()))
				{
					if (dynamic_cast<CCandle *>(colliable_objects->at(i)))
					{
						CEffectDatabase::GetInstance()->AddHitEffect(colliable_objects->at(i)->x, colliable_objects->at(i)->y);
						dynamic_cast<CCandle *>(colliable_objects->at(i))->ChangeAnimation();
					}
					
				}

			}
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			
			if (dynamic_cast<CBrick *>(coEventsResult[0]->obj))
			{
				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;
			}
			


			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CCandle *>(e->obj) )
				{
					dynamic_cast<CCandle *>(e->obj)->ChangeAnimation();
					CEffectDatabase::GetInstance()->AddHitEffect(e->obj->x, e->obj->y);
				}
				else if (dynamic_cast<CEnemy*>(e->obj) && !dynamic_cast<CEnemy*>(e->obj)->isBurning)
				{

					CEffectDatabase::GetInstance()->AddHitEffect(e->obj->x, e->obj->y);

					if (dynamic_cast<CGhost*>(e->obj))
						CSimon::GetInstance()->Score += KILL_GHOST_SCORE;
					else if (dynamic_cast<CBat*>(e->obj) || dynamic_cast<CPanther*>(e->obj))
						CSimon::GetInstance()->Score += KILL_BAT_SCORE;
					else if (dynamic_cast<CKappa*>(e->obj))
						CSimon::GetInstance()->Score += KILL_KAPPA_SCORE;
					dynamic_cast<CEnemy*>(e->obj)->ChangeAnimation();


				}
				else if (dynamic_cast<CBrick*>(e->obj) && this->Currentstate==0)
				{
					this->Currentstate = 1;
					y -=10;
					StartBurn();
				
				}



			}

		}

		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	}
	
}

void CHolyWater::GetBoundingBox(float &x, float &y, float &framew, float &frameh)
{
	if (Currentstate == 0)
	{
		x = this->x;
		y = this->y;
		framew = 16;
		frameh = 16;
	}
	else
	{
		x = this->x;
		y = this->y;
		framew = 32;
		frameh = 26;
	}
	
}
void CHolyWater::Render()
{
	animation->Render(x, y, default_color);
	RenderBoundingBox();
}
