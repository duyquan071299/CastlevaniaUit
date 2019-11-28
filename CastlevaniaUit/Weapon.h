#pragma once
#include"GameObject.h"

class CWeapon :public CGameObject
{
protected:
	LPANIMATION animation;
	HolderType WeaponType;
public:
	virtual void Update(DWORD dt, unordered_set<LPGAMEOBJECT> coObjects){}
	bool isContain(RECT rect1, RECT rect2)
	{
		if (rect1.left > rect2.right || rect1.right < rect2.left || rect1.top > rect2.bottom || rect1.bottom < rect2.top)
		{
			return false;
		}

		return true;
	}
	virtual void Render()
	{
		
		
	}
	HolderType GetType() { return WeaponType; }
};
