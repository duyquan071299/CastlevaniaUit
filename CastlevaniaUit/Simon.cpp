#include"Simon.h"
#include"SimonStateStanding.h"
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

	ani = new CAnimation(180);
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

	ani = new CAnimation(180);
	ani->Add(PLAYER, 13);
	ani->Add(PLAYER, 14);
	ani->Add(PLAYER, 15);
	animations[ATTACKING_STAND_RIGHT] = ani;
	this->y = 225;

	//currentanimation= animations[STANDING_RIGHT];
	ChangeState(new CSimonStateStanding(STANDING_RIGHT));
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
	
}
void CSimon::OnKeyUp(int keyCode)
{
	
}

void CSimon::Update(DWORD dt)
{
	
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