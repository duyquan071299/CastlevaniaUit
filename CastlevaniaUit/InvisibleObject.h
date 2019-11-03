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

	virtual void GetBoundingBox(float &x, float &y, float &framew, float &frameh){
		x = this->x;
		y = this->y;
		framew = this->Width;
		frameh = this->Height;
	}
};