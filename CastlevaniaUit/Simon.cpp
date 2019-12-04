#include"Simon.h"
#include"SimonStateStanding.h"
#include"SimonStateJumping.h"
#include"SimonStateAttacking.h"
#include"SimonStateSitting.h"
#include"SimonStateInjured.h"

CSimon * CSimon::instance = NULL;

CSimon::CSimon() {

	//LEFT ANIMATION
	animations[STANDING_LEFT] = CAnimationDatabase::GetInstance()->Get(SIMON_ANI, STANDING_LEFT);
	animations[WALKING_LEFT] = CAnimationDatabase::GetInstance()->Get(SIMON_ANI, WALKING_LEFT);
	animations[SITTING_LEFT] = CAnimationDatabase::GetInstance()->Get(SIMON_ANI, SITTING_LEFT);
	animations[ATTACKING_STAND_LEFT] = CAnimationDatabase::GetInstance()->Get(SIMON_ANI, ATTACKING_STAND_LEFT);
	animations[ATTACKING_SIT_LEFT] = CAnimationDatabase::GetInstance()->Get(SIMON_ANI, ATTACKING_SIT_LEFT);
	animations[ONSTAIR_STANDING_DOWN_LEFT] = CAnimationDatabase::GetInstance()->Get(SIMON_ANI, ONSTAIR_STANDING_DOWN_LEFT);
	animations[ONSTAIR_WALKING_DOWN_LEFT] = CAnimationDatabase::GetInstance()->Get(SIMON_ANI, ONSTAIR_WALKING_DOWN_LEFT);
	animations[ONSTAIR_STANDING_UP_LEFT] = CAnimationDatabase::GetInstance()->Get(SIMON_ANI, ONSTAIR_STANDING_UP_LEFT);
	animations[ONSTAIR_WALKING_UP_LEFT] = CAnimationDatabase::GetInstance()->Get(SIMON_ANI, ONSTAIR_WALKING_UP_LEFT);
	animations[ONSTAIR_DOWN_ATTACK_LEFT] = CAnimationDatabase::GetInstance()->Get(SIMON_ANI, ONSTAIR_DOWN_ATTACK_LEFT);
	animations[ONSTAIR_UP_ATTACK_LEFT] = CAnimationDatabase::GetInstance()->Get(SIMON_ANI, ONSTAIR_UP_ATTACK_LEFT);
	animations[INJURED_LEFT] = CAnimationDatabase::GetInstance()->Get(SIMON_ANI, INJURED_LEFT);
	//RIGHT ANIMATION
	animations[STANDING_RIGHT] = CAnimationDatabase::GetInstance()->Get(SIMON_ANI, STANDING_RIGHT);
	animations[WALKING_RIGHT] = CAnimationDatabase::GetInstance()->Get(SIMON_ANI, WALKING_RIGHT);
	animations[SITTING_RIGHT] = CAnimationDatabase::GetInstance()->Get(SIMON_ANI, SITTING_RIGHT);
	animations[ATTACKING_STAND_RIGHT] = CAnimationDatabase::GetInstance()->Get(SIMON_ANI, ATTACKING_STAND_RIGHT);
	animations[ATTACKING_SIT_RIGHT] = CAnimationDatabase::GetInstance()->Get(SIMON_ANI, ATTACKING_SIT_RIGHT);
	animations[ONSTAIR_STANDING_DOWN_RIGHT] = CAnimationDatabase::GetInstance()->Get(SIMON_ANI, ONSTAIR_STANDING_DOWN_RIGHT);
	animations[ONSTAIR_WALKING_DOWN_RIGHT] = CAnimationDatabase::GetInstance()->Get(SIMON_ANI, ONSTAIR_WALKING_DOWN_RIGHT);
	animations[ONSTAIR_STANDING_UP_RIGHT] = CAnimationDatabase::GetInstance()->Get(SIMON_ANI, ONSTAIR_STANDING_UP_RIGHT);
	animations[ONSTAIR_WALKING_UP_RIGHT] = CAnimationDatabase::GetInstance()->Get(SIMON_ANI, ONSTAIR_WALKING_UP_RIGHT);
	animations[ONSTAIR_DOWN_ATTACK_RIGHT] = CAnimationDatabase::GetInstance()->Get(SIMON_ANI, ONSTAIR_DOWN_ATTACK_RIGHT);
	animations[ONSTAIR_UP_ATTACK_RIGHT] = CAnimationDatabase::GetInstance()->Get(SIMON_ANI, ONSTAIR_UP_ATTACK_RIGHT);
	animations[INJURED_RIGHT] = CAnimationDatabase::GetInstance()->Get(SIMON_ANI, INJURED_RIGHT);



	this->IsDead = true;

	
}


void CSimon::Respawn()
{
	if (IsDead == true)
	{
		
		WhipLevel = WHIP_START_LEVEL;
		Heart = HEART_START;
		Life = LIFE_START;
		Heal = HEAL_START;
		LifeTime = TIME_START;
		WeaponType = HEART;
		Count_Time = GetTickCount();
		ChangeState(new CSimonStateStanding(STANDING_RIGHT));
		nx = 1;
		IsDead = false;
	}
	else
	{
		this->y = RESPAWN_POSITION_Y;
		this->x = SIMON_START_POS_X;
	}
	
	
	
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
	if (CollectItem == true)
	{
		color = D3DCOLOR_ARGB(255, rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
		currentanimation->GetCurrenrFrame()->Draw(x, y, color);
	}
	else if (Untouchable == true && (IsStanding || IsSitting || IsJumping || IsAttacking||isOnStair||IsMoving ))
	{
		color = D3DCOLOR_ARGB(rand() % 255 +1, 255, 255, 255 );
		currentanimation->Render(x, y, color);
	}
	else
		currentanimation->Render(x, y, color);

	
	RenderBoundingBox();
	
}

void CSimon::OnKeyDown(int keyCode)
{
	if (isCollect == true)
		return;
	switch (keyCode)
	{
	case DIK_SPACE:
		if ((IsStanding || IsMoving)&&!IsJumping&&!isOnStair)
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
		if (isOnStair && !IsAttacking)
		{
			whip = new CWhip();
			whip->SetType(WhipLevel);
			IsSitting = false;
			if (DirectionStair==1)
			{
				if(CSimon::GetInstance()->isUP)
					ChangeState(new CSimonStateAttacking(ONSTAIR_UP_ATTACK_RIGHT));
				else
					ChangeState(new CSimonStateAttacking(ONSTAIR_DOWN_ATTACK_LEFT));
			}
			else
			{
				if (CSimon::GetInstance()->isUP)
					ChangeState(new CSimonStateAttacking(ONSTAIR_UP_ATTACK_LEFT));
				else
					ChangeState(new CSimonStateAttacking(ONSTAIR_DOWN_ATTACK_RIGHT));

			}

		}
		else if ((IsStanding|| IsMoving|| IsOnAir) && !IsAttacking&&!isThrowing )
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
	if (GetTickCount() - CollectItem_Time > COLLECT_ITEM_TIME && CollectItem_Time!=0)
	{
		CollectItem = false;
	
		CollectItem_Time = 0;

	}

	if (GetTickCount() - Count_Time > 1000)
	{
		LifeTime--;
		Count_Time = GetTickCount();
	}

	if (GetTickCount() -  Untouchable_Time> UNTOUCHABLE_TIME)
	{
		if (Untouchable == true)
			isInjured = false;
		Untouchable = false;
		Untouchable_Time = 0;

	}

	if (GetTickCount() - Landing_Time > LANDING_TIME)
	{
		Landing = false;
		Landing_Time = 0;

	}
	if (CollectItem == true)
		return;
	// Calculate dx, dy 
	CGameObject::Update(dt);
	
	
	// Free Fall	
	if ((!this->IsJumping && !this->IsFalling && !this->IsAttacking &&!this->isCollect &&!this->isOnStair && vy > GAME_GRAVITY * dt+0.4 &&vy<1000)||isInjured&&vy==0&&!isOnStair  )
	{

		vy += 5000 * GAME_GRAVITY * dt;
		isFreeFall = true;
	}
	else if(!isOnStair)
		vy += GAME_GRAVITY * dt;

	
	if (isFreeFall)
	{
		StartLanding();
		isFreeFall = false;
		if (nx >= 0)
			ChangeState(new CSimonStateSitting(SITTING_RIGHT));
		else
			ChangeState(new CSimonStateSitting(SITTING_LEFT));
	}
	CheckCollisionWithBrick(coObjects);
	CheckCollisionWithInvisibleObject(coObjects);
	CheckCollisionWithStair(coObjects);
	CheckCollisionWithItem(coObjects);
	CheckCollisionWithEnemy(coObjects);

	/*
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
	
		isColiableWithStairBottom = isColiableWithStairTop = false;

		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (isContain(this->GetBBox(), coObjects->at(i)->GetBBox()) && !dynamic_cast<CDagger*>(coObjects->at(i)))
			{

				if (dynamic_cast<CItem *>(coObjects->at(i)))
				{
				
					CItem *Item = dynamic_cast<CItem *>(coObjects->at(i));
					if (Item->GetHolderType() == LARGE_HEART)
						this->Heart += 5;
					else if (Item->GetHolderType() == HEART)
						this->Heart += 1;
					else if (Item->GetHolderType() == WHIP)
					{
						StartCollectItem();
						this->WhipLevel += 1;
					}
					else if (Item->GetHolderType() == DAGGER)
					{
						
							ChangeSecondWeapon(DAGGER);
					}
					else if (Item->GetHolderType() == WATCH)
					{
						ChangeSecondWeapon(WATCH);
					}
					else if (Item->GetHolderType() == CROSS)
					{
						isUsingCross = true;
					}
					else if (Item->GetHolderType() == HOLYWATER)
					{
						ChangeSecondWeapon(HOLYWATER);
					}
					else if (Item->GetHolderType() == MONEY_1)
					{
						this->Score += 100;
					}
					else if (Item->GetHolderType() == MONEY_2)
					{
						this->Score += 200;
					}
					else if (Item->GetHolderType() == MONEY_3)
					{
						this->Score += 300;
					}
					Item->IsDead = true;
				}
				else if (dynamic_cast<CInvisibleObject *>(coObjects->at(i)))
				{
					if (dynamic_cast<CInvisibleObject *>(coObjects->at(i))->GetType() == UP_STAIR_OBJECT_TYPE_1)
					{
						if (isColiableWithStairTop)
							continue;
						isColiableWithStairBottom = true;
						DirectionStair = 1;
						CheckPoint = dynamic_cast<CInvisibleObject *>(coObjects->at(i))->x + 5;
					}
					else if (dynamic_cast<CInvisibleObject *>(coObjects->at(i))->GetType() == DOWN_STAIR_OBJECT_TYPE_1)
					{
						if (isOnStair)
						{
							isOnStair = false;
							isInjured = false;
							if (DirectionStair)
							{
								nx = 1;
								ChangeState(new CSimonStateStanding(STANDING_RIGHT));
							}
							y -= 2;
							vy = 9999.0f;
							vx = 0.0f;
						}
						else
						{
							isColiableWithStairTop = true;
							DirectionStair = 1;
							CheckPoint = dynamic_cast<CInvisibleObject *>(coObjects->at(i))->x;
						}
							
					}
					else if (dynamic_cast<CInvisibleObject *>(coObjects->at(i))->GetType() == UP_STAIR_OBJECT_TYPE_2)
					{
						isColiableWithStairBottom = true;
						DirectionStair = -1;
						CheckPoint = dynamic_cast<CInvisibleObject *>(coObjects->at(i))->x ;
					}
					else if (dynamic_cast<CInvisibleObject *>(coObjects->at(i))->GetType() == DOWN_STAIR_OBJECT_TYPE_2)
					{
						if (isOnStair)
						{
							isOnStair = false;
							isInjured = false;
							if (DirectionStair)
							{
								nx = -1;
								ChangeState(new CSimonStateStanding(STANDING_LEFT));
							}
							y -= 2;
							vy = 9999.0f;
							vx = 0.0f;
						}
						else
						{
							isColiableWithStairTop = true;
							DirectionStair = -1;
							CheckPoint = dynamic_cast<CInvisibleObject *>(coObjects->at(i))->x;
						}
					}
						
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
			if (isOnStair && !isUP)
			{
				if (nx <= 0 && ny>=0)
				{
					x += dx;
				}
				else
				{
					isOnStair = false;
					if (DirectionStair == 1)
					{
						nx = -1;
						ChangeState(new CSimonStateStanding(STANDING_LEFT));
						CSimon::GetInstance()->isInjured = false;

					}
					else if (DirectionStair == -1)
					{
						nx = 1;
						ChangeState(new CSimonStateStanding(STANDING_RIGHT));
						CSimon::GetInstance()->isInjured = false;
					}
				}
				
				

			}
			
			if (ny == 1)
			{
				y += dy;
			}
			
		}
	
				
		if (!dynamic_cast<CInvisibleObject*>(coEventsResult[0]->obj)&& !dynamic_cast<CItem*>(coEventsResult[0]->obj))
		{
			if (nx != 0)
			{
				if(vy>0 &&!isOnStair)
					vx = 0;
			}
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
					else if (Item->GetHolderType() == HEART)
						this->Heart += 1;
					else if (Item->GetHolderType() == WHIP)
					{
						StartCollectItem();
						this->WhipLevel += 1;
					}	
					else if (Item->GetHolderType() == DAGGER)
					{
							ChangeSecondWeapon(DAGGER);
					}
					else if (Item->GetHolderType() == WATCH)
					{
						
							ChangeSecondWeapon(WATCH);
					}
					else if (Item->GetHolderType() == CROSS)
					{
						isUsingCross = true;
					}
					else if (Item->GetHolderType() == HOLYWATER)
					{
						ChangeSecondWeapon(HOLYWATER);
					}
					else if (Item->GetHolderType() == MONEY_1)
					{
						this->Score += 100;
					}
					else if (Item->GetHolderType() == MONEY_2)
					{
						this->Score += 200;
					}
					else if (Item->GetHolderType() == MONEY_3)
					{
						this->Score += 300;
					}
					Item->IsDead = true;
			
			}
			else if (dynamic_cast<CEnemy *>(e->obj) || dynamic_cast<CEnemyBullet *>(e->obj))
			{
				this->Heal -= 1;
				if (dynamic_cast<CBat *>(e->obj))
					dynamic_cast<CBat *>(e->obj)->ChangeAnimation();

				if (isOnStair || IsOnAnimation)
				{
					StartUntouchable();
					isInjured = true;
					vx = 0;
					vy = 0;
				}
				else
				{
					if (nx <= 0 && ny <= 0)
					{
						vx = -INJURED_SPEED_X;
					}
					else
						vx = INJURED_SPEED_X;

					vy = -INJURED_SPEED_Y;
					
					this->IsJumping=false;
					if (vx <= 0)
						CSimon::GetInstance()->ChangeState(new CSimonStateInjured(INJURED_LEFT));
					else
						CSimon::GetInstance()->ChangeState(new CSimonStateInjured(INJURED_RIGHT));

				}
			
					
		
			}
			else if (dynamic_cast<CInvisibleObject*>(e->obj))
			{
				//this->IsOnAnimation = true;
				CInvisibleObject* object = dynamic_cast<CInvisibleObject *>(e->obj);
				if (object->GetType() == WALK_THROUGH_DOOR_OBJECT)
				{
					CCamera::GetInstance()->isWithSimon = false;
					CheckPoint = object->x + object->GetWidth();
					this->y = GROUND_POSITION_Y;
					object->IsDead = true;
					ChangeState(new CSimonStateStanding(STANDING_RIGHT));
					IsFreeze = true;

				}
				else if (object->GetType() == WALK_THROUGH_CASTLE_OBJECT)
				{
					CCamera::GetInstance()->isWithSimon = false;
					IsOnAnimation = true;
					if (vx > 0)
						CheckPoint = x + CHECK_POINT_1;
					else
						CheckPoint = x - CHECK_POINT_2;
					if (vy != 0)
					{
						vy = 99999.0f;
						y -= 2;
						if (vx > 0)
							ChangeState(new CSimonStateWalking(WALKING_RIGHT));
						else
							ChangeState(new CSimonStateWalking(WALKING_LEFT));
					}


					object->IsDead = true;
				}
				else if (object->GetType() == IN_CASTLE_OBJECT)
				{
					this->IsOnAnimation = false;
					this->IsRespawn = true;
					object->IsDead = true;
				}
				else if (object->GetType() == WALK_IN_UNDER_GROUND_OBJECT)
				{
					if (!IsOnAnimation)
					{
						MoveToLocation(CHECK_POINT_4,0.0f);
						CheckPoint = object->x - CHECK_POINT_3;
						vx = -SIMON_ONSTAIR_SPEED * 4;
						vy = -SIMON_ONSTAIR_SPEED * 4;
						this->IsOnAnimation = true;
						isWalkingInOutGround = true;
					}
					else
						this->isUnderGround = true;
				
					x += dx;
				}
				else if (object->GetType() == WALK_OUT_UNDER_GROUND_OBJECT)
				{
					if (!IsOnAnimation)
					{
						MoveToLocation(-CHECK_POINT_4,0.0f);
						CheckPoint = object->x+ CHECK_POINT_2;
						vx = SIMON_ONSTAIR_SPEED * 4;
						vy = SIMON_ONSTAIR_SPEED * 4;
						this->IsOnAnimation = true;
						isWalkingInOutGround = true;
					}
					else
						this->isUnderGround = false;
					x += dx;

				}


			}
				this->isCollect = false;
		}



	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	*/
	

	currentstate->Update(dt);

}


void CSimon::HandleKeyboard(unordered_map<int, bool> keys)
{
	if(!IsOnAnimation && !isCollect)
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
	if (isOnStair)
	{
		if (nx > 0)
		{
			x = this->x + 16;
			y = this->y + 4;
			framew = 32;
			frameh = 63;
		}
		else
		{
			x = this->x + 12;
			y = this->y + 4;
			framew = 32;
			frameh = 63;
		}
	}
	else if(IsSitting)
	{
		if (nx > 0)
		{
			x = this->x + 16;
			y = this->y + 20;
			framew = 32;
			frameh = 44;
		}
		else
		{
			x = this->x + 12;
			y = this->y + 20;
			framew = 32;
			frameh = 44;
		}
	}
	else
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
			x = this->x + 12;
			y = this->y + 4;
			framew = 32;
			frameh = 60;
		}
	}
	

	
}
CWeapon* CSimon::CreateSecondWeapond()
{
	CWeapon* NewWeapon;

	switch (WeaponType)
	{
	case DAGGER:
	{
		CDagger* Dagger = new CDagger();
		Dagger->SetPosition(x + 8, y);
		if (isOnStair)
		{
			if (DirectionStair == 1)
			{
				if (isUP)
				{
					Dagger->ChangeAnimation(20);
					Dagger->nx = 1;
				}
				else
				{
					Dagger->ChangeAnimation(19);
					Dagger->nx = -1;
				}

			}
			else
			{

				if (isUP)
				{
					Dagger->ChangeAnimation(19);
					Dagger->nx = -1;
				}
				else
				{
					Dagger->ChangeAnimation(20);
					Dagger->nx = 1;
				}
			}
		}
		else
		{
			if (nx > 0)
			{
				Dagger->ChangeAnimation(20);
				Dagger->nx = 1;
			}
			else
			{
				Dagger->ChangeAnimation(19);
				Dagger->nx = -1;
			}

		}
		return Dagger;
	}
	case AXE:
		break;
	case HOLYWATER:
	{
		CHolyWater * HolyWater = new CHolyWater();
		HolyWater->Currentstate = 0;
		HolyWater->SetPosition(x + 8, y + 32);
		if (isOnStair)
		{
			if (DirectionStair == 1)
			{
				if (isUP)
				{

					HolyWater->nx = 1;
				}
				else
				{
					HolyWater->nx = -1;
				}

			}
			else
			{

				if (isUP)
				{

					HolyWater->nx = -1;
				}
				else
				{
					HolyWater->nx = 1;
				}
			}
		}
		else
		{
			if (nx > 0)
			{
				HolyWater->nx = 1;


			}
			else
			{

				HolyWater->nx = -1;

			}

		}
		HolyWater->SetAnimation();
		return HolyWater;
	}
	}
		
}

void CSimon::CheckCollisionWithStair(vector<LPGAMEOBJECT> *coObjects)
{
	
	vector<LPGAMEOBJECT> ListInvisibleObject;
	ListInvisibleObject.clear();
	int type;
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CInvisibleObject *>(coObjects->at(i)))
		{
			int type = dynamic_cast<CInvisibleObject *>(coObjects->at(i))->GetType();
			if (type == UP_STAIR_OBJECT_TYPE_1 || type == DOWN_STAIR_OBJECT_TYPE_1 || type == UP_STAIR_OBJECT_TYPE_2 || type == DOWN_STAIR_OBJECT_TYPE_2)
			{
				ListInvisibleObject.push_back(coObjects->at(i));
			}
		}
	}

	
			
	isColiableWithStairBottom = isColiableWithStairTop = false;
	for (UINT i = 0; i < ListInvisibleObject.size(); i++)
	{
		
		if (isContain(this->GetBBox(), ListInvisibleObject.at(i)->GetBBox()))
		{
			if (dynamic_cast<CInvisibleObject *>(ListInvisibleObject.at(i))->GetType() == UP_STAIR_OBJECT_TYPE_1)
			{
				if (isColiableWithStairTop)
					continue;
				isColiableWithStairBottom = true;
				DirectionStair = 1;
				CheckPoint = dynamic_cast<CInvisibleObject *>(ListInvisibleObject.at(i))->x + 5;
			}
			else if (dynamic_cast<CInvisibleObject *>(ListInvisibleObject.at(i))->GetType() == DOWN_STAIR_OBJECT_TYPE_1)
			{
				if (isOnStair)
				{
					isOnStair = false;
					isInjured = false;
					if (DirectionStair)
					{
						nx = 1;
						ChangeState(new CSimonStateStanding(STANDING_RIGHT));
					}
					y -= 2;
					vy = 9999.0f;
					vx = 0.0f;
				}
				else
				{
					isColiableWithStairTop = true;
					DirectionStair = 1;
					CheckPoint = dynamic_cast<CInvisibleObject *>(ListInvisibleObject.at(i))->x;
				}

			}
			else if (dynamic_cast<CInvisibleObject *>(ListInvisibleObject.at(i))->GetType() == UP_STAIR_OBJECT_TYPE_2)
			{
				isColiableWithStairBottom = true;
				DirectionStair = -1;
				CheckPoint = dynamic_cast<CInvisibleObject *>(ListInvisibleObject.at(i))->x;
			}
			else if (dynamic_cast<CInvisibleObject *>(ListInvisibleObject.at(i))->GetType() == DOWN_STAIR_OBJECT_TYPE_2)
			{
				if (isOnStair)
				{
					isOnStair = false;
					isInjured = false;
					if (DirectionStair)
					{
						nx = -1;
						ChangeState(new CSimonStateStanding(STANDING_LEFT));
					}
					y -= 2;
					vy = 9999.0f;
					vx = 0.0f;
				}
				else
				{
					isColiableWithStairTop = true;
					DirectionStair = -1;
					CheckPoint = dynamic_cast<CInvisibleObject *>(ListInvisibleObject.at(i))->x;
				}
			}

		}
	}
}

void CSimon::CheckCollisionWithBrick(vector<LPGAMEOBJECT> *coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPGAMEOBJECT> ListBrick;
	ListBrick.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (dynamic_cast<CBrick *>(coObjects->at(i)))
			ListBrick.push_back(coObjects->at(i));

	CalcPotentialCollisions(&ListBrick, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;
		if (isOnStair && !isUP)
		{
			if (nx <= 0 && ny >= 0)
			{
				x += dx;
			}
			else
			{
				isOnStair = false;
				if (DirectionStair == 1)
				{
					nx = -1;
					ChangeState(new CSimonStateStanding(STANDING_LEFT));
					CSimon::GetInstance()->isInjured = false;

				}
				else if (DirectionStair == -1)
				{
					nx = 1;
					ChangeState(new CSimonStateStanding(STANDING_RIGHT));
					CSimon::GetInstance()->isInjured = false;
				}
			}



		}

		if (ny == 1)
		{
			y += dy;
		}

		if (nx != 0)
		{
			if (vy > 0 && !isOnStair)
				vx = 0;
		}
		if (ny == -1) vy = 0;
	}
	
}

void CSimon::CheckCollisionWithInvisibleObject(vector<LPGAMEOBJECT> *coObjects)
{

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	vector<LPGAMEOBJECT> ListInvisibleObject;
	ListInvisibleObject.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CInvisibleObject *>(coObjects->at(i)))
		{
			if (dynamic_cast<CInvisibleObject *>(coObjects->at(i)))
			{
				if (dynamic_cast<CInvisibleObject *>(coObjects->at(i))->GetType() != WALK_THROUGH_CASTLE_OBJECT && dynamic_cast<CInvisibleObject *>(coObjects->at(i))->GetType() != IN_CASTLE_OBJECT && dynamic_cast<CInvisibleObject *>(coObjects->at(i))->GetType() != WALK_THROUGH_DOOR_OBJECT && dynamic_cast<CInvisibleObject *>(coObjects->at(i))->GetType() != WALK_OUT_UNDER_GROUND_OBJECT && dynamic_cast<CInvisibleObject *>(coObjects->at(i))->GetType() != WALK_IN_UNDER_GROUND_OBJECT)
					continue;
				if (dynamic_cast<CInvisibleObject *>(coObjects->at(i))->GetType() == WALK_OUT_UNDER_GROUND_OBJECT || dynamic_cast<CInvisibleObject *>(coObjects->at(i))->GetType() == WALK_IN_UNDER_GROUND_OBJECT)
					if (!isOnStair)
						continue;
				if (dynamic_cast<CInvisibleObject *>(coObjects->at(i))->GetType() == IN_CASTLE_OBJECT && !this->IsOnAnimation)
					continue;
				ListInvisibleObject.push_back(coObjects->at(i));
			}
		}
	}
		
	CalcPotentialCollisions(&ListInvisibleObject, coEvents);

	if (coEvents.size() == 0)
	{
		return;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		LPCOLLISIONEVENT e = coEventsResult[0];
		CInvisibleObject* object = dynamic_cast<CInvisibleObject *>(e->obj);
		if (object->GetType() == WALK_THROUGH_DOOR_OBJECT)
		{
			CCamera::GetInstance()->isWithSimon = false;
			CheckPoint = object->x + object->GetWidth();
			this->y = GROUND_POSITION_Y;
			object->IsDead = true;
			ChangeState(new CSimonStateStanding(STANDING_RIGHT));
			IsFreeze = true;

		}
		else if (object->GetType() == WALK_THROUGH_CASTLE_OBJECT)
		{
			CCamera::GetInstance()->isWithSimon = false;
			IsOnAnimation = true;
			if (vx > 0)
				CheckPoint = x + CHECK_POINT_1;
			else
				CheckPoint = x - CHECK_POINT_2;
			if (vy != 0)
			{
				vy = 99999.0f;
				y -= 2;
				if (vx > 0)
					ChangeState(new CSimonStateWalking(WALKING_RIGHT));
				else
					ChangeState(new CSimonStateWalking(WALKING_LEFT));
			}


			object->IsDead = true;
		}
		else if (object->GetType() == IN_CASTLE_OBJECT)
		{
			this->IsOnAnimation = false;
			this->IsRespawn = true;
			object->IsDead = true;
		}
		else if (object->GetType() == WALK_IN_UNDER_GROUND_OBJECT)
		{
			if (!IsOnAnimation)
			{
				MoveToLocation(CHECK_POINT_4, 0.0f);
				CheckPoint = object->x - CHECK_POINT_3;
				vx = -SIMON_ONSTAIR_SPEED * 4;
				vy = -SIMON_ONSTAIR_SPEED * 4;
				this->IsOnAnimation = true;
				isWalkingInOutGround = true;
			}
			else
				this->isUnderGround = true;

			x += dx;
		}
		else if (object->GetType() == WALK_OUT_UNDER_GROUND_OBJECT)
		{
			if (!IsOnAnimation)
			{
				MoveToLocation(-CHECK_POINT_4, 0.0f);
				CheckPoint = object->x + CHECK_POINT_2;
				vx = SIMON_ONSTAIR_SPEED * 4;
				vy = SIMON_ONSTAIR_SPEED * 4;
				this->IsOnAnimation = true;
				isWalkingInOutGround = true;
			}
			else
				this->isUnderGround = false;
			x += dx;

		}
	}


}

void CSimon::CheckCollisionWithItem(vector<LPGAMEOBJECT> *coObjects)
{

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	bool isColideUsingAABB=false;
	HolderType type;
	coEvents.clear();
	vector<LPGAMEOBJECT> ListItem;
	ListItem.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (dynamic_cast<CItem *>(coObjects->at(i)))
		{
			ListItem.push_back(coObjects->at(i));
		}
	for (UINT i = 0; i < ListItem.size(); i++)
	{
		if (isContain(this->GetBBox(), ListItem.at(i)->GetBBox()))
		{
			isColideUsingAABB = true;
			CItem *Item = dynamic_cast<CItem *>(ListItem.at(i));
			type = Item->GetHolderType();
			Item->IsDead = true;
			break;

		}
			
	}
	

	if (isColideUsingAABB != true)
	{
		CalcPotentialCollisions(&ListItem, coEvents);
		if (coEvents.size() == 0)
		{
			return;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			LPCOLLISIONEVENT e = coEventsResult[0];
			CItem *Item = dynamic_cast<CItem *>(e->obj);
			type = Item->GetHolderType();
			Item->IsDead = true;
		}

	}
	


	if (type == LARGE_HEART)
		this->Heart += 5;
	else if (type == HEART)
		this->Heart += 1;
	else if (type == WHIP)
	{
		StartCollectItem();
		this->WhipLevel += 1;
	}
	else if (type == DAGGER)
	{

		ChangeSecondWeapon(DAGGER);
	}
	else if (type == WATCH)
	{
		ChangeSecondWeapon(WATCH);
	}
	else if (type == CROSS)
	{
		isUsingCross = true;
	}
	else if (type == HOLYWATER)
	{
		ChangeSecondWeapon(HOLYWATER);
	}
	else if (type == MONEY_1)
	{
		this->Score += 100;
	}
	else if (type == MONEY_2)
	{
		this->Score += 200;
	}
	else if (type == MONEY_3)
	{
		this->Score += 300;
	}
}


void CSimon::CheckCollisionWithEnemy(vector<LPGAMEOBJECT> *coObjects)
{

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	bool isColideUsingAABB = false;
	coEvents.clear();
	vector<LPGAMEOBJECT> ListEnemy;
	ListEnemy.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (dynamic_cast<CEnemy *>(coObjects->at(i)) || dynamic_cast<CEnemyBullet *>(coObjects->at(i)))
		{
			ListEnemy.push_back(coObjects->at(i));
		}
	for (UINT i = 0; i < ListEnemy.size(); i++)
	{
		if (isContain(this->GetBBox(), ListEnemy.at(i)->GetBBox()))
		{
			isColideUsingAABB = true;
			
			this->Heal -= 1;
			if (Untouchable || isInjured)
				continue;
			
			if (dynamic_cast<CBat *>(ListEnemy.at(i)))
				dynamic_cast<CBat *>(ListEnemy.at(i))->ChangeAnimation();

			if (isOnStair)
			{
				StartUntouchable();
				isInjured = true;
				vx = 0;
				vy = 0;
			}
			else
			{
				vx = -nx * 0.1;
				vy = -0.5;
				this->IsJumping = false;
				if (vx <= 0)
					CSimon::GetInstance()->ChangeState(new CSimonStateInjured(INJURED_LEFT));
				else
					CSimon::GetInstance()->ChangeState(new CSimonStateInjured(INJURED_RIGHT));

			}
			return;

		}

	}




	

	if (isColideUsingAABB != true)
	{
		CalcPotentialCollisions(&ListEnemy, coEvents);
		if (coEvents.size() == 0)
		{
			return;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			LPCOLLISIONEVENT e = coEventsResult[0];
			if (dynamic_cast<CBat *>(e->obj))
				dynamic_cast<CBat *>(e->obj)->ChangeAnimation();

			this->Heal -= 1;
			if (isOnStair || IsOnAnimation)
			{
				StartUntouchable();
				isInjured = true;
				vx = 0;
				vy = 0;
			}
			else
			{
				if (nx <= 0 && ny <= 0)
				{
					vx = -INJURED_SPEED_X;
				}
				else
					vx = INJURED_SPEED_X;

				vy = -INJURED_SPEED_Y;

				this->IsJumping = false;
				if (vx <= 0)
					CSimon::GetInstance()->ChangeState(new CSimonStateInjured(INJURED_LEFT));
				else
					CSimon::GetInstance()->ChangeState(new CSimonStateInjured(INJURED_RIGHT));

			}
		}

	}


}