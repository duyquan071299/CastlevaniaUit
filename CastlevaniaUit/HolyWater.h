#pragma once
#include"Weapon.h"
#include"Simon.h"
#include"Ghost.h"

class CHolyWater : public CWeapon
{

	unordered_map<State, LPANIMATION> animations;
	

public:
	CHolyWater();
	~CHolyWater() {}
	int Currentstate;
	DWORD LifeTime;
	virtual void Update(DWORD dt, unordered_set<LPGAMEOBJECT> coObjects);
	void StartBurn() { LifeTime = GetTickCount(); }
	virtual void GetBoundingBox(float &x, float &y, float &framew, float &frameh);
	void Render();


};
