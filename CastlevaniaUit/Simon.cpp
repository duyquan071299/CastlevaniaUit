#include"Simon.h"
CSimon * CSimon::instance = NULL;

CSimon::CSimon() {
	//LEFT ANIMATION
	LPANIMATION ani = new CAnimation(100);
	ani->Add(PLAYER,0);
	animations[STANDING_LEFT] = ani;

	ani = new CAnimation(100);
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

	currentanimation= animations[STANDING_RIGHT];
}


CSimon::~CSimon()
{
	for (auto it = animations.begin(); it != animations.end(); ++it)
	{
		if (it->second) delete it->second;
		animations.erase(it);
	}
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


	if (keyCode == DIK_RIGHT)
	{
		currentanimation = animations[WALKING_RIGHT];
	}
	else if (keyCode == DIK_LEFT)
	{
		currentanimation = animations[WALKING_LEFT];
	}
	else if (keyCode == DIK_DOWN)
	{
		currentanimation = animations[SITTING_RIGHT];
	}
	else if (keyCode == DIK_X)
	{
		currentanimation = animations[ATTACKING_STAND_RIGHT];
	}
}
void CSimon::OnKeyUp(int keyCode) {
	if (keyCode == DIK_X)
	{
		currentanimation = animations[WALKING_RIGHT];
	}
}