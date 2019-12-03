#pragma once
#include"GameObject.h"


class CBrick :public CGameObject
{
	int Type;
	int Width;
	int Height;
	LPSPRITE BrickSprite;
	State CurrentState;
public:
	bool isHit;
	CBrick() {}
	CBrick(float x, float y) {
		this->x = x;
		this->y = y;
		this->dx = 0;
		this->dy = 0;
		this->vx = 0;
		this->vy = 0;
		this->IsDead = false;
		
	}
	void SetType(int type)
	{
		this->Type = type;
		if (this->Type == 3  || this->Type == 6|| this->Type==7)
		{
			BrickSprite = CSpriteDatabase::GetInstance()->GetSprite(GROUND, 1);
		}
		else if (this->Type == 4)
		{
			BrickSprite = CSpriteDatabase::GetInstance()->GetSprite(GROUND, 0);
		}
		else if (this->Type == 5)
		{
			BrickSprite = CSpriteDatabase::GetInstance()->GetSprite(GROUND, 2);
		}

		
		
	}
	void SetWH(int width, int height) { Width = width; Height = height; }
	int GetType() { return this->Type; }
	
	~CBrick() {}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render();
	virtual void GetBoundingBox(float &x, float &y, float &framew, float &frameh);
};