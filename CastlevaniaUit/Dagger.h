#pragma once
#include"Weapon.h"

class CDagger : public CWeapon
{
	
public:
	CDagger();
	//~CWhip();
	
	void Update(DWORD dt);
	void Render();


};