#pragma once
#include"GameObject.h"
#include"Item.h"

class CCandle:public CGameObject
{
	LPANIMATION animation;
	HolderType HDType;
	int Width;
	int Height;
	int CandleType;

	
public:
	bool isBurning;
	CCandle(int x,int y,HolderType type, int CandleType);
	~CCandle(){}
	HolderType  GetHolder() { return HDType; }
	void ChangeAnimation();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void SetWH(int width, int height) { Width = width; Height = height; }
	void Render();
	virtual void GetBoundingBox(float &x, float &y, float &framew, float &frameh);
};