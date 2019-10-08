#pragma once
#include"SimonState.h"
#include"SimonStateWalking.h"

class CSimonStateStanding :public CSimonState
{
public: 
	CSimonStateStanding() {};
	CSimonStateStanding(SimonState Name) { 
		
		StateName = Name;
	}
	void Update(DWORD dt);
	void HandleKeyboard(unordered_map<int, bool> keyCode);
	void SetState(SimonState Name) {
		StateName = Name;
	}
	void Exit();
	void Enter();



};
