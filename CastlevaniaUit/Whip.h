#pragma once
#include"Weapon.h"

class CWhip : public CWeapon
{
	unordered_map<ItemType, LPANIMATION> animations;

public:
	CWhip();
	//~CWhip();
	void Update(DWORD dt);
	void Render();
	void ChangeWeaponState(ItemType);

};