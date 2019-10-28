#include"Simon.h"
#include"SimonStateStanding.h"
#include"SimonStateJumping.h"
#include"SimonStateAttacking.h"

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
	
}


void CSimon::Respawn()
{
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
void CSimon::Wall(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	/*CGameObject::Update(dt);*/

	// Simple fall down
	//vy += GAME_GRAVITY * dt;


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();


	// turn off collision when die 
	//if (currentstate->GetStateName() != MARIO_STATE_DIE)
	CalcPotentialCollisions(coObjects, coEvents);
	// reset untouchable timer if untouchable time has passed

	// No collision occured, proceed normally
	/*if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;

	}
	else*/
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}
void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);
	
	// Simple fall down
	vy += GAME_GRAVITY * dt;
	

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	

	// turn off collision when die 
	//if (currentstate->GetStateName() != MARIO_STATE_DIE)
	CalcPotentialCollisions(coObjects, coEvents);
	// reset untouchable timer if untouchable time has passed
	DWORD now = GetTickCount();
	if (GetTickCount() - Untouchable_Time > COLLECT_ITEM_TIME)
	{
		Untouchable = false;
		Untouchable_Time = 0;
		
	}
	if (Untouchable == true)
		return;

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
 		x += dx;
		y += dy;

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
		}

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CItem *>(e->obj))
			{
					CItem *Item = dynamic_cast<CItem *>(e->obj);
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
