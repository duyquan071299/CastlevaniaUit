#pragma once
#include"SimonState.h"
#include"SimonStateStanding.h"

class CSimonStateWalking :public CSimonState
{
public:
	CSimonStateWalking() {};
	CSimonStateWalking(SimonState Name) { StateName = Name; };
	void Update(DWORD dt);
	void HandleKeyboard(unordered_map<int, bool> keyCode);
	void SetState(SimonState State) {
		StateName= State;
	};
	void Exit();
	void Enter();
};