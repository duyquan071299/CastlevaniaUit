#pragma once
#include"GameObject.h"


class CBrick :public CGameObject
{
	int Type;
	int Width;
	int Height;
public:
	CBrick() {}
	CBrick(float x, float y) {
		this->x = x;
		this->y = y;
		this->dx = 0;
		this->dy = 0;
		this->vx = 0;
		this->vy = 0;
	}
	void SetType(int type)
	{
		this->Type = type;
	}
	void SetWH(int width, int height) { Width = width; Height = height; }
	int GetType() { return this->Type; }
	
	~CBrick() {}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render();
	virtual void GetBoundingBox(float &x, float &y, float &framew, float &frameh);
};