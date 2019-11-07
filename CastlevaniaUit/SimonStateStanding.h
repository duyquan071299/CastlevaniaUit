#pragma once
#include"SimonState.h"
#include"SimonStateWalking.h"

class CSimonStateStanding :public CSimonState
{
public: 
	CSimonStateStanding() {};
	CSimonStateStanding(State Name) {
		StateName = Name;
	}
	void Update(DWORD dt);
	void HandleKeyboard(unordered_map<int, bool> keyCode);
	void SetState(State Name) {
		StateName = Name;
	}
	void Exit();
	void Enter();



};
