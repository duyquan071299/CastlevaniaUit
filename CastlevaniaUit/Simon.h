#pragma once
#include"GameObject.h"
#include"SimonSprites.h"
#include"SimonState.h"
#include"Whip.h"
#include"Item.h"
#include"Dagger.h"
#include"Brick.h"

class CSimonState;
class Whip;
class CSimon :public CGameObject
{
private:
	static CSimon* instance;
	unordered_map<SimonState, LPANIMATION> animations;
	LPANIMATION currentanimation;
	CSimonState* currentstate;
	SimonState StateName;
	bool Untouchable;
	

	DWORD Untouchable_Time;
	DWORD Landing_Time;
	int Heart;


public:
	CSimon();
	~CSimon();
	LPANIMATION getCurrentAnimation() { return currentanimation; }
	CWhip* whip;
	CWeapon* SecondWeapon;
	bool Landing;
	bool IsKeyDownZ;
	int count=0;
	int WhipLevel = 1;
	bool IsStanding = true, IsSitting = false, IsMoving = false, IsAttacking = false, IsJumping = false, IsFalling = false, IsOnAir = false,isThrowing=false,isHitting=false,isFreeFall=false,isCollect=false;
	void ChangeState(CSimonState* State);
	void SetStateName(SimonState Name)
	{
		StateName = Name;
	}
	void StartUntouchable() { Untouchable = true; Untouchable_Time = GetTickCount(); }
	void StartLanding() { Landing = true; Landing_Time = GetTickCount(); }

	void SetCurrentAnimation(SimonState Name)
	{
		currentanimation = animations[Name];
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Respawn();
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
	void ChangeSecondWeapon(CWeapon* type)
	{
		delete SecondWeapon;
		SecondWeapon = type;
	}
	void Render();

	virtual void GetBoundingBox(float &x, float &y, float &framew, float &frameh);
};