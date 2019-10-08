#pragma once
#include"SimonState.h"
#include"SimonStateStanding.h"

class CSimonStateJumping :public CSimonState
{
public:
	CSimonStateJumping() {};
	CSimonStateJumping(SimonState Name) { StateName = Name; };
	void Update(DWORD dt);
	void HandleKeyboard(unordered_map<int, bool> keyCode);
	void SetState(SimonState State) {
		StateName = State;
	};
	void Exit();
	void Enter();
}; 
