#pragma once
#include"Simon.h"
class CSimonState
{
protected:
	SimonState StateName;
public:
	CSimonState() {};
	~CSimonState() {};
	virtual void Update(DWORD dt) = 0;
	virtual void HandleKeyboard(unordered_map<int, bool> keyCode) = 0;
	virtual void SetState(SimonState Name) = 0;
	virtual void Exit()=0;
	virtual void Enter() = 0;
	SimonState GetStateName() { return StateName; }

};
