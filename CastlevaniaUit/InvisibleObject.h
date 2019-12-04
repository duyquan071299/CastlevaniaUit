#pragma once
#include"GameObject.h"


class CInvisibleObject :public CGameObject
{
	int InvisibleType;
	int Width;
	int Height;
public:
	CInvisibleObject() {}
	CInvisibleObject(float x, float y) {
		this->x = x;
		this->y = y;
		this->dx = 0;
		this->dy = 0;
		this->vx = 0;
		this->vy = 0;
	}
	void SetType(int type)
	{
		this->InvisibleType = type;
	}
	void SetWH(int width, int height) { Width = width; Height = height; }
	int GetType() { return this->InvisibleType; }

	~CInvisibleObject() {}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL){}
	void Render(){
		RenderBoundingBox();
	}
	int GetWidth()
	{
		return this->Width;
	}
	virtual void GetBoundingBox(float &x, float &y, float &framew, float &frameh){
		x = this->x;
		y = this->y;
		framew = (float)this->Width;
		frameh = (float)this->Height;
	}
};