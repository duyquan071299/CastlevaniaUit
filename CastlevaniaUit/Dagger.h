#pragma once
#include"Weapon.h"
#include"Simon.h"
#include"Ghost.h"

class CDagger : public CWeapon
{
	LPANIMATION animation;

	
public:
	CDagger();
	~CDagger(){}
	
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void ChangeAnimation(int index);
	virtual void GetBoundingBox(float &x, float &y, float &framew, float &frameh);
	void Render();


};
