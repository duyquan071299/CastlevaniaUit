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

	ani = new CAnimation(195);
	ani->Add(PLAYER, 0,10);
	ani->Add(PLAYER, 5);
	ani->Add(PLAYER, 6);
	ani->Add(PLAYER, 7);
	animations[ATTACKING_STAND_LEFT] = ani;
	//RIGHT ANIMATION
	ani = new CAnimation(100);
	ani->Add(PLAYER, 8);
	animations[STANDING_RIGHT] = ani;

	ani = new CAnimation(180);
	ani->Add(PLAYER, 8);
	ani->Add(PLAYER, 9);
	ani->Add(PLAYER, 10);
	ani->Add(PLAYER, 11);
	animations[WALKING_RIGHT] = ani;

	ani = new CAnimation(100);
	ani->Add(PLAYER, 12);
	animations[SITTING_RIGHT] = ani;

	ani = new CAnimation(150);
	ani->Add(PLAYER, 8,10);
	ani->Add(PLAYER, 13);
	ani->Add(PLAYER, 14);
	ani->Add(PLAYER, 15);
	animations[ATTACKING_STAND_RIGHT] = ani;


	this->y = 225;

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
	currentanimation->Render(x,y);
}

void CSimon::OnKeyDown(int keyCode)
{
	switch (keyCode)
	{
	case DIK_Z:
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
	case DIK_X:
		if ((IsStanding == true || IsMoving == true || IsJumping == true) && IsAttacking != true)
		{
			if (nx > 0)
			{
				IsAttacking = true;
				ChangeState(new CSimonStateAttacking(ATTACKING_STAND_RIGHT));
			}
			else
			{
				IsAttacking = true;
				ChangeState(new CSimonStateAttacking(ATTACKING_STAND_LEFT));
			
			}

		}
		break;
	}
}
void CSimon::OnKeyUp(int keyCode)
{
	
}

void CSimon::Update(DWORD dt)
{
	
	y += vy * dt;
	x += vx * dt;
	vy += GAME_GRAVITY * dt;
	if (y > 225)
	{
		IsJumping = false;
		vy = 0;
		y = 225;
	}
	

}



void CSimon::HandleKeyboard(unordered_map<int, bool> keys)
{
	currentstate->HandleKeyboard(keys);
}

void CSimon::ChangeState(CSimonState* State) {
	delete currentstate;
	currentstate = State;
	StateName = State->GetStateName();
	currentanimation = animations[StateName];
}