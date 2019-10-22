#pragma once
#include"GameObject.h"


class CBrick :public CGameObject
{
	int Type;
	int Width;
	int Height;
public:
	void SetType(int type)
	{
		this->Type = type;
	}
	void SetWH(int width, int height) { Width = width; Height = height; }
	int GetType() { return this->Type; }
	CBrick(){}
	CBrick(float x, float y){
		this->x = x;
		this->y = y;
	}
	~CBrick() {}
	void Update(DWORD dt){}
	void Render();
	virtual void GetBoundingBox(float &x, float &y, float &framew, float &frameh);
};