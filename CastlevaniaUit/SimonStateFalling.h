#pragma once
#include"SimonState.h"
#include"SimonStateStanding.h"

class CSimonStateFalling :public CSimonState
{
public:
	CSimonStateFalling() {};
	CSimonStateFalling(SimonState Name) { StateName = Name; };
	void Update(DWORD dt);
	void HandleKeyboard(unordered_map<int, bool> keyCode);
	void SetState(SimonState State) {
		StateName = State;
	};
	void Exit();
	void Enter();
};
