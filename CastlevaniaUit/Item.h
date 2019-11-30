#pragma once
#include"GameObject.h"

class CItem : public CGameObject
{
	LPANIMATION animation;
	int Width;
	int Height;
	bool isOnGround;
	int MaxMov = y;
	HolderType HDType;
	DWORD lifetime;


public:
	bool isAppearOnMap;
	CItem();
	CItem(HolderType type);
	~CItem(){}
	HolderType GetHolderType() { return this->HDType; }
	void GetBoundingBox(float &x, float &y, float &framew, float &frameh);
	void AppearOnMap() 
	{ 
		lifetime = GetTickCount();
		isAppearOnMap = true;
	}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);


};
