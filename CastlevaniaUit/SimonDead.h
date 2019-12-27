#pragma once
#include"SimonState.h"
#include"SimonStateStanding.h"

class CSimonStateDead :public CSimonState
{
public:
	CSimonStateDead() {};
	CSimonStateDead(State Name) { StateName = Name; };
	void Update(DWORD dt);
	void HandleKeyboard(unordered_map<int, bool> keyCode);
	void SetState(State State) {
		StateName = State;
	};
	void Exit();
	void Enter();
};