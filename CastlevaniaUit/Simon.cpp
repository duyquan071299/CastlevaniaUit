#include"Simon.h"
#include"SimonStateStanding.h"
#include"SimonStateJumping.h"
#include"SimonStateAttacking.h"
#include"SimonStateSitting.h"

CSimon * CSimon::instance = NULL;

CSimon::CSimon() {
	//LEFT ANIMATION
	LPANIMATION ani = new CAnimation(100);
	ani->Add(PLAYER,0);
	animations[STANDING_LEFT] = ani;

	ani = new CAnimation(180);
	ani->Add(PLAYER, 0);
	ani->Add(PLAYER, 1);
	ani->Add(PLAYER, 2);
	ani->Add(PLAYER, 3);
	animations[WALKING_LEFT] = ani;

	ani = new CAnimation(100);
	ani->Add(PLAYER, 4);
	animations[SITTING_LEFT] = ani;

	ani = new CAnimation(100);
	ani->Add(PLAYER, 0,10);
	ani->Add(PLAYER, 5);
	ani->Add(PLAYER, 6);
	ani->Add(PLAYER, 7);
	animations[ATTACKING_STAND_LEFT] = ani;

	ani = new CAnimation(100);
	ani->Add(PLAYER, 4, 10);
	ani->Add(PLAYER, 8);
	ani->Add(PLAYER, 9);
	ani->Add(PLAYER, 10);
	animations[ATTACKING_SIT_LEFT] = ani;

	ani = new CAnimation(100);
	ani->Add(PLAYER, 22);
	animations[ONSTAIR_STANDING_LEFT] = ani;

	ani = new CAnimation(180);
	ani->Add(PLAYER, 22);
	ani->Add(PLAYER, 23);
	animations[ONSTAIR_UP_LEFT] = ani;

	ani = new CAnimation(180);
	ani->Add(PLAYER, 24);
	ani->Add(PLAYER, 23);
	animations[ONSTAIR_DOWN_LEFT] = ani;

	ani = new CAnimation(100);
	ani->Add(PLAYER, 25);
	ani->Add(PLAYER, 26);
	ani->Add(PLAYER, 27);
	animations[ONSTAIR_UP_ATTACK_LEFT] = ani;
	ani = new CAnimation(100);
	ani->Add(PLAYER, 28);
	ani->Add(PLAYER, 29);
	ani->Add(PLAYER, 30);
	animations[ONSTAIR_DOWN_ATTACK_LEFT] = ani;
	

	//RIGHT ANIMATION
	ani = new CAnimation(100);
	ani->Add(PLAYER,11);
	animations[STANDING_RIGHT] = ani;

	ani = new CAnimation(180);
	ani->Add(PLAYER, 11);
	ani->Add(PLAYER, 12);
	ani->Add(PLAYER, 13);
	ani->Add(PLAYER, 14);
	animations[WALKING_RIGHT] = ani;

	ani = new CAnimation(100);
	ani->Add(PLAYER, 15);
	animations[SITTING_RIGHT] = ani;

	ani = new CAnimation(100);
	ani->Add(PLAYER, 11,10);
	ani->Add(PLAYER, 16);
	ani->Add(PLAYER, 17);
	ani->Add(PLAYER, 18);
	animations[ATTACKING_STAND_RIGHT] = ani;

	ani = new CAnimation(100);
	ani->Add(PLAYER, 15, 10);
	ani->Add(PLAYER, 19);
	ani->Add(PLAYER, 20);
	ani->Add(PLAYER, 21);
	animations[ATTACKING_SIT_RIGHT] = ani;

	ani = new CAnimation(100);
	ani->Add(PLAYER, 31);
	animations[ONSTAIR_STANDING_RIGHT] = ani;

	ani = new CAnimation(180);
	ani->Add(PLAYER, 31);
	ani->Add(PLAYER, 32);
	animations[ONSTAIR_UP_RIGHT] = ani;

	ani = new CAnimation(180);
	ani->Add(PLAYER, 33);
	ani->Add(PLAYER, 32);
	animations[ONSTAIR_DOWN_RIGHT] = ani;

	ani = new CAnimation(100);
	ani->Add(PLAYER, 34);
	ani->Add(PLAYER, 35);
	ani->Add(PLAYER, 36);
	animations[ONSTAIR_UP_ATTACK_RIGHT] = ani;

	ani = new CAnimation(100);
	ani->Add(PLAYER, 37);
	ani->Add(PLAYER, 38);
	ani->Add(PLAYER, 39);
	animations[ONSTAIR_DOWN_ATTACK_RIGHT] = ani;




	
}


void CSimon::Respawn()
{
	//this->y = 217;
	this->y = 0;
	//currentanimation= animations[STANDING_RIGHT];
	ChangeState(new CSimonStateStanding(STANDING_RIGHT));
	nx = 1;
}


CSimon::~CSimon()
{
	for (auto it = animations.begin(); it != animations.end(); ++it)
	{
		if (it->second) delete it->second;
		animations.erase(it);
	}
	if (currentstate != nullptr)
		delete currentstate;
	currentstate = nullptr;
}

CSimon* CSimon:: GetInstance()
{
	if (instance == NULL)
		instance = new CSimon();
	return instance;
}

void CSimon::Render()
{
	if (whip != nullptr)
		whip->Render();
	D3DCOLOR color = default_color;
	if (Untouchable == true)
	{
		color = D3DCOLOR_ARGB(255, rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
		currentanimation->GetCurrenrFrame()->Draw(x, y, color);
	}
	else
		currentanimation->Render(x, y, color);

	
	RenderBoundingBox();
	
}

void CSimon::OnKeyDown(int keyCode)
{
	if (Untouchable == true)
		return;
	switch (keyCode)
	{
	case DIK_SPACE:
		if ((IsStanding == true || IsMoving == true)&&IsJumping!=true)
		{
			if (nx > 0)
			{
			
				IsJumping = true;
				ChangeState(new CSimonStateJumping(SITTING_RIGHT));
				vy = -SIMON_JUMPING_SPEED;
			}
			else
			{
				IsJumping = true;
				ChangeState(new CSimonStateJumping(SITTING_LEFT));
				vy = -SIMON_JUMPING_SPEED;
			}
		
		}
		break;
	case DIK_Z:
		IsKeyDownZ = true;
		if ((IsStanding|| IsMoving|| IsOnAir) && !IsAttacking&&!isThrowing )
		{
			whip = new CWhip();
			whip->SetType(WhipLevel);
			IsSitting = false;
			if (nx > 0)
			{
				ChangeState(new CSimonStateAttacking(ATTACKING_STAND_RIGHT));
			}
			else
			{
				ChangeState(new CSimonStateAttacking(ATTACKING_STAND_LEFT));
			
			}
		}
		else if (IsSitting && !IsAttacking)
		{
			whip = new CWhip();
			whip->SetType(WhipLevel);
			
			if (nx > 0)
			{
				ChangeState(new CSimonStateAttacking(ATTACKING_SIT_RIGHT));
				
			}
			else
			{
				ChangeState(new CSimonStateAttacking(ATTACKING_SIT_LEFT));

			}
			IsSitting = true;
		}
		
		break;
		
		

	}
}

void CSimon::OnKeyUp(int keyCode)
{
	if(keyCode==DIK_Z)
		CSimon::GetInstance()->IsKeyDownZ = false;
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{

	// reset untouchable timer if untouchable time has passed
	DWORD now = GetTickCount();
	if (GetTickCount() - Untouchable_Time > COLLECT_ITEM_TIME)
	{
		Untouchable = false;
		Untouchable_Time = 0;

	}
	if (GetTickCount() - Landing_Time > LANDING_TIME)
	{
		Landing = false;
		Landing_Time = 0;

	}
	if (Untouchable == true)
		return;
	// Calculate dx, dy 
	CGameObject::Update(dt);
	
	// Simple fall down	
	if (!this->IsJumping && !this->IsFalling && !this->IsAttacking &&!this->isCollect && vy > GAME_GRAVITY * dt+0.4 )
	{
		vy += 20 * GAME_GRAVITY * dt;
		isFreeFall = true;
	}
	else
		vy += GAME_GRAVITY * dt;
	

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	
	

	// turn off collision when die 
	//if (currentstate->GetStateName() != MARIO_STATE_DIE)
	CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
 		x += dx;
		y += dy;

		if (isFreeFall)
		{
			StartLanding();
			isFreeFall = false;
			if (nx >= 0)
				ChangeState(new CSimonStateSitting(SITTING_RIGHT));
			else
				ChangeState(new CSimonStateSitting(SITTING_LEFT));
		}

		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (isContain(this->GetBBox(), coObjects->at(i)->GetBBox()) && !dynamic_cast<CDagger*>(coObjects->at(i)))
			{

				if (dynamic_cast<CItem *>(coObjects->at(i)))
				{
				
					CItem *Item = dynamic_cast<CItem *>(coObjects->at(i));
					if (Item->GetHolderType() == LARGE_HEART)
						this->Heart += 5;
					else if (Item->GetHolderType() == WHIP)
					{
						StartUntouchable();
						this->WhipLevel += 1;
					}
					else if (Item->GetHolderType() == DAGGER)
					{
						if (this->SecondWeapon == nullptr)
							this->SecondWeapon = new CDagger();
						else
							ChangeSecondWeapon(new CDagger());
					}

					Item->IsDead = true;
				}
			}
		}
		
	}
	else
	{
	
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		if (dynamic_cast<CBrick *>(coEventsResult[0]->obj))
		{
			x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
			y += min_ty * dy + ny * 0.4f;

			if (ny == 1)
			{
				y += dy;
			}
			
		}
	
		if (dynamic_cast<CInvisibleObject*>(coEventsResult[0]->obj))
		{
			//this->IsOnAnimation = true;
			CInvisibleObject*Object = dynamic_cast<CInvisibleObject *>(coEventsResult[0]->obj);
			if (Object->GetType() == 1)
			{
				//this->x = 1344;
				this->IsOnAnimation = true;
				Object->IsDead = true;
			}
			else if(Object->GetType() == 2)
			{

				this->IsOnAnimation = false;
				this->IsRespawn = true;
				Object->IsDead = true;
			}
				

			
			
		}

		if (!dynamic_cast<CInvisibleObject*>(coEventsResult[0]->obj)&& !dynamic_cast<CItem*>(coEventsResult[0]->obj))
		{
			if (nx != 0) vx = 0;
			if (ny ==-1) vy = 0;
		}
		
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CItem *>(e->obj))
			{
					CItem *Item = dynamic_cast<CItem *>(e->obj);
					isCollect = true;
					if (Item->IsDead == true)
						continue;
					if (Item->GetHolderType() == LARGE_HEART)
						this->Heart += 5;
					else if (Item->GetHolderType() == WHIP)
					{
						StartUntouchable();
						this->WhipLevel += 1;
					}
						
					else if (Item->GetHolderType() == DAGGER)
					{
						if (this->SecondWeapon == nullptr)
							this->SecondWeapon = new CDagger();
						else
							ChangeSecondWeapon(new CDagger());
					}
					Item->IsDead = true;
			
			}
			else if (dynamic_cast<CEnemy *>(e->obj))
			{
				if (nx < 0)
				{
					vx = -0.2;
				}
				else
					vx = 0.2;
				
				vy = -SIMON_JUMPING_SPEED;
			}
				
				this->isCollect = false;
		}



	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (whip != nullptr)
		whip->Update(dt, coObjects);
	currentstate->Update(dt);

}


void CSimon::HandleKeyboard(unordered_map<int, bool> keys)
{
	if(!IsOnAnimation)
		currentstate->HandleKeyboard(keys);
}

void CSimon::ChangeState(CSimonState* State) {
	if(currentstate)
		currentstate->Exit();
	delete currentstate;
	currentstate = State;
	currentstate->Enter();
	StateName = State->GetStateName();
	currentanimation = animations[StateName];
}

void CSimon::GetBoundingBox(float &x, float &y, float &framew, float &frameh)
{
	if (nx > 0)
	{
		x = this->x + 16;
		y = this->y + 4;
		framew = 32;
		frameh = 60;
	}
	else
	{
		x = this->x+12;
		y = this->y+4;
		framew = 32;
		frameh = 60;
	}
	
}
