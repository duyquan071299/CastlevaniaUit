#pragma once
#include"GameObject.h"

#include"SimonSprites.h"
#include"SimonState.h"

class CSimonState;
class CSimon :public CGameObject
{
private:
	static CSimon* instance;
	unordered_map<SimonState, LPANIMATION> animations;
	LPANIMATION currentanimation;
	CSimonState* currentstate;
	SimonState StateName;

public:
	CSimon();
	~CSimon();
	LPANIMATION getCurrentAnimation() { return currentanimation; }
	//CSimonState* getCurrentState() { return currentstate; }
	bool IsStanding = true, IsSitting = false, IsMoving = false, IsAttacking = false, IsJumping = false, IsFalling = false, IsOnAir = false;
	void ChangeState(CSimonState* State);
	void SetStateName(SimonState Name)
	{
		StateName = Name;
	}
	void SetCurrentAnimation(SimonState Name)
	{
		currentanimation = animations[Name];
	}
	void Update(DWORD dt);
	void Respawn();
	void HandleKeyboard(unordered_map<int, bool> keys);
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	static CSimon* GetInstance();
	void Render();
};