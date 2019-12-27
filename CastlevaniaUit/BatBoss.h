#pragma once
#include"Enemy.h"

#define BOSS_WIDTH 96.0f
#define BOSS_HEIGHT 46.0f

#define AFTER_ATTACK_ZONE_X_LEFT 5200.0f
#define AFTER_ATTACK_ZONE_X_RIGHT 5600.0f
#define AFTER_ATTACK_ZONE_Y_TOP 100.0f
#define AFTER_ATTACK_ZONE_Y_BOTTOM 200.0f
#define ATTACK_ZONE_X_LEFT 5200.0f
#define ATTACK_ZONE_X_RIGHT 5400.0f
#define ATTACK_ZONE_Y_1_TOP 120.0f
#define ATTACK_ZONE_Y_1_BOTTOM 216.0f
#define ATTACK_ZONE_Y_2_TOP 220.0f
#define ATTACK_ZONE_Y_2_BOTTOM 285.0f
#define ATTACK_ZONE_Y_3_TOP 290.0f
#define ATTACK_ZONE_Y_3_BOTTOM 330.0f
#define ATTACK_RANGE_1 340
#define ATTACK_RANGE_2 265
#define RANDOM_DISTANCE_TO_SIMON 100
#define BOSS_BASE_SPEED 0.05f
#define BOSS_BASE_HEAL 16
#define BEGIN_MOVE 1
#define ATTACK_MOVE 2
#define AFTER_ATTACK_MOVE 3
#define READY_ATTACK_MOVE 4




class CBatBoss :public CEnemy
{
protected:


	State CurrentState;
	int MovingState;
	int Heal;


	float x1, y1;
	float x2, y2;
	float x3, y3;
	float perc;

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

	void  SetCurrentState(State state) { this->CurrentState = state; this->curAnimation = animations[state]; }

	void SetHeal(int Heal) { this->Heal = Heal; }

	void AttackMovement();
	
	void StartWait() { TimeTilNextMove = GetTickCount(); IsWaitTilNextMove = true; }

	int getPt(int n1, int n2, float perc)
	{
		int diff = n2 - n1;

		return n1 + (diff * perc);
	}

	void AfterAttackMovement();

	void ReadyAttack();




	int GetHeal () { return this->Heal; }
	virtual void GetBoundingBox(float &x, float &y, float &framew, float &frameh);

	void ChangeAnimation(){}
	int Random(int a, int b);
};