#pragma once
#include"Weapon.h"
#include"Candle.h"
#include"Ghost.h"
#include"EnemyBullet.h"
#include"Brick.h"
class CWhip : public CWeapon
{
	unordered_map<ItemType, LPANIMATION> animations;
	int WhipType = 1;
	int WhipWidth;

public:
	CWhip();
	//~CWhip();
	void SetType(int type) {
		WhipType = type;
	}
	int GetType() {
		return this->WhipType;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects=NULL);
	void Render();
	void ChangeWeaponState(int nx);
	virtual void GetBoundingBox(float &x, float &y, float &framew, float &frameh);

};