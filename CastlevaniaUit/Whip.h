#pragma once
#include"Weapon.h"

class CWhip : public CWeapon
{
	unordered_map<ItemType, LPANIMATION> animations;
	int WhipType = 1;
public:
	CWhip();
	//~CWhip();
	void SetType(int type) {
		WhipType = type;
	}
	int GetType() {
		return this->WhipType;
	}
	void Update(DWORD dt);
	void Render();
	void ChangeWeaponState(int nx);

};