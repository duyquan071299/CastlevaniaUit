#pragma once
#include"Weapon.h"

class CEnemyBullet : public CWeapon
{
	LPANIMATION animation;

	bool isBurning;
public:
	CEnemyBullet();
	CEnemyBullet(float x, float y,int direction);
	~CEnemyBullet() {}

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void ChangeAnimation(int index);
	void ChangeAnimation();
	virtual void GetBoundingBox(float &x, float &y, float &framew, float &frameh);
	void Render();


};
