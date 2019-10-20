#pragma once
#include"GameObject.h"
class CItem : public CGameObject
{
	LPANIMATION animation;
	int Width;
	int Height;
	HolderType HDType;

public:
	CItem();
	CItem(HolderType type);
	~CItem(){}
	HolderType GetHolderType() { return this->HDType; }
	void GetBoundingBox(float &x, float &y, float &framew, float &frameh);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);


};
