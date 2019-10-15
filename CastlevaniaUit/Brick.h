#pragma once
#include"GameObject.h"


class CBrick :public CGameObject
{
	int Type;
	LPSPRITE Sprite;
public:
	void SetType(int type)
	{
		this->Type = type;
	}
	int GetType() { return this->Type; }
	void SetSprite(LPSPRITE sprite)
	{
		this->Sprite = sprite;
	}
	LPSPRITE GetSprite()
	{
		return this->Sprite;
	}
	CBrick(){
		type = BRICK;
	}
	~CBrick() {}
	void Update(DWORD dt){}
	void Render();
	virtual void GetBoundingBox(float &x, float &y, float &framew, float &frameh);
};