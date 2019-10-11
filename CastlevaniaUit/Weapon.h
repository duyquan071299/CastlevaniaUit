#pragma once
#include"GameObject.h"

class CWeapon :public CGameObject
{
protected:
	LPANIMATION animation;
	virtual void Update(DWORD dt) {};
	virtual void Render()
	{
		
		
	}
};
