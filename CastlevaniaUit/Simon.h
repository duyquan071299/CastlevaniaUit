#pragma once
#include"GameObject.h"
#include"SimonSprites.h"
#include"SimonState.h"
#include"AnimationDatabase.h"
#include"Whip.h"
#include"Item.h"
#include"Dagger.h"
#include"StopWatch.h"
#include"Brick.h"
#include"InvisibleObject.h"
#include"Camera.h"
#include"EnemyBullet.h"
#include"Bat.h"
#include"HolyWater.h"
#include"Axe.h"
class CSimonState;
class Whip;
#define SIMON_START_POS_Y 217.0f
#define SIMON_START_POS_X 0.0f
#define WHIP_START_LEVEL 1
#define HEART_START 5
#define LIFE_START 3
#define HEAL_START 16
#define TIME_START 300
#define SIMON_START_POS_X 0.0f
#define INJURED_SPEED_X 0.1
#define INJURED_SPEED_Y 0.5
#define RESPAWN_POS_INDOOR_X 0
#define RESPAWN_BAT_X 3200
#define RESPAWN_BOSS_X 4200
#define SMALL_HEART_ITEM 1
#define HEAL_REGAIN 5
#define LARGE_HEART_ITEM 5
#define MONEY_1_SCORE 100
#define MONEY_2_SCORE 200
#define FREE_FALL_SPEED 5000
#define MONEY_3_SCORE 300


class CSimon :public CGameObject
{
private:
	static CSimon* instance;
	unordered_map<State, LPANIMATION> animations;
	LPANIMATION currentanimation;
	CSimonState* currentstate;
	State StateName;
	
	DWORD Untouchable_Time;
	DWORD Landing_Time;
	DWORD CollectItem_Time;
	DWORD Count_Time;


public:
	CSimon();
	~CSimon();
	LPANIMATION getCurrentAnimation() { return currentanimation; }
	CWhip* whip;
	HolderType WeaponType;
	bool Landing;
	bool CollectItem;
	int DirectionStair;
	float CheckPoint;
	int PreviousX, PreviousY;
	bool IsKeyDownZ;
	int count=0;
	int WhipLevel = 1;
	int WeaponShot;
	bool IsStanding,IsSitting,IsMoving, IsAttacking,IsJumping,IsFalling , IsOnAir,isThrowing,isHitting,isFreeFall,isCollect,isOnStair,isUP,isInjured;
	bool IsOnAnimation;
	bool isUsingStopWatch;
	bool isUsingCross;
	bool AllowThrow;
	bool IsFreeze;
	bool isColiableWithStairBottom;
	bool isColiableWithStairTop;
	bool isUnderGround;
	bool isWalkingInOutGround;
	bool isThroughDoorOne;
	bool isThroughDoorTwo;
	bool isActiveBoss;
	bool Untouchable;
	int AtLevel;
	int Heart, Life,Score,LifeTime,Heal;
	bool IsRespawn;
	bool IsWalkToCastle;
	bool IsLoading;
	void ChangeState(CSimonState* State);
	void SetStateName(State Name)
	{
		StateName = Name;
	}
	void StartUntouchable() { Untouchable = true; Untouchable_Time = GetTickCount(); }
	void StartCollectItem() {
		CollectItem = true;
		CollectItem_Time = GetTickCount(); }
	void StartLanding() { Landing = true; Landing_Time = GetTickCount(); }
	bool isUntouchable() { return Untouchable; }
	void SetCurrentAnimation(State Name)
	{
		currentanimation = animations[Name];
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Respawn(int Stage);
	void HandleKeyboard(unordered_map<int, bool> keys);
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	bool isContain(RECT rect1, RECT rect2)
	{
		if (rect1.left > rect2.right || rect1.right < rect2.left || rect1.top > rect2.bottom || rect1.bottom < rect2.top)
		{
			return false;
		}

		return true;
	}
	static CSimon* GetInstance();
	void ChangeSecondWeapon(HolderType type)
	{
		WeaponType = type;
		
	}
	void Render();

	virtual void GetBoundingBox(float &x, float &y, float &framew, float &frameh);

	CWeapon * CreateSecondWeapond();

	void MoveToLocation(float x, float y)
	{
		this->x += x;
		this->PreviousX += x;
		this->y += y;
		this->PreviousY += y;
	}
	void CheckCollisionWithStair(vector<LPGAMEOBJECT> *coObjects=NULL);

	void CheckCollisionWithBrick(vector<LPGAMEOBJECT> *coObjects = NULL);

	void CheckCollisionWithInvisibleObject(vector<LPGAMEOBJECT> *coObjects = NULL);

	void CheckCollisionWithItem(vector<LPGAMEOBJECT> *coObjects = NULL);


	void CheckCollisionWithEnemy(vector<LPGAMEOBJECT> *coObjects = NULL);
	void LoadVariable();

};