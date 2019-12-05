#pragma once
#include"Enemy.h"

#define BOSS_WIDTH 96.0f
#define BOSS_HEIGHT 46.0f
class CBatBoss :public CEnemy
{
protected:
	State CurrentState;
	int MovingState;
	int Heal;
	float PreviousX;
	float PreviousY;
	float LandingX;
	float LandingY;

	DWORD TimeTilNextMove;
	bool IsWaitTilNextMove;
	

public:
	CBatBoss();
	CBatBoss(float x, float y);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);

	void Render();

	void StartMoving();

	State GetCurrentState() { return CurrentState; }

	void  SetCurrentState(State state) { this->CurrentState = state; }

	void SetHeal(int Heal) { this->Heal = Heal; }

	int GetHeat() { return this->Heal; }
	virtual void GetBoundingBox(float &x, float &y, float &framew, float &frameh);

	void ChangeAnimation(){}

};