#pragma once
#include"Weapon.h"
#include"Simon.h"


class CStopWatch : public CWeapon
{


public:
	CStopWatch();
	~CStopWatch() {}

	virtual void Update(DWORD dt, unordered_set<LPGAMEOBJECT> coObjects);
	virtual void GetBoundingBox(float &x, float &y, float &framew, float &frameh){ }


};
