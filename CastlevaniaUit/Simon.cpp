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

	ani = new CAnimation(100);
	ani->Add(PLAYER, 5);
	ani->Add(PLAYER, 6);
	ani->Add(PLAYER, 7);
	animations[ATTACKING_STAND_LEFT] = ani;
	//RIGHT ANIMATION
	ani = new CAnimation(100);
	ani->Add(PLAYER, 31);
	animations[STANDING_RIGHT] = ani;

	ani = new CAnimation(100);
	ani->Add(PLAYER, 30);
	ani->Add(PLAYER, 29);
	ani->Add(PLAYER, 28);
	animations[WALKING_RIGHT] = ani;

	ani = new CAnimation(100);
	ani->Add(PLAYER, 27);
	animations[SITTING_RIGHT] = ani;

	ani = new CAnimation(100);
	ani->Add(PLAYER, 26);
	ani->Add(PLAYER, 25);
	ani->Add(PLAYER, 24);
	animations[ATTACKING_STAND_RIGHT] = ani;

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

}