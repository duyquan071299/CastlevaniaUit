#pragma once
#include"Simon.h"
class CSimonState
{
protected:
	State StateName;
public:
	CSimonState() {};
	~CSimonState() {};
	virtual void Update(DWORD dt) = 0;
	virtual void HandleKeyboard(unordered_map<int, bool> keyCode) = 0;
	virtual void SetState(State Name) = 0;
	virtual void Exit()=0;
	virtual void Enter() = 0;
	State GetStateName() { return StateName; }

};
