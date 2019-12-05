#pragma once
#include"Weapon.h"
#include"Simon.h"
#include"Ghost.h"
#define AXE_SPEED_X 0.3
#define AXE_SPEED_Y -0.65
class CAxe : public CWeapon
{
	LPANIMATION animation;


public:
	CAxe();
	~CAxe() {}

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void GetBoundingBox(float &x, float &y, float &framew, float &frameh);
	void Render();


};
