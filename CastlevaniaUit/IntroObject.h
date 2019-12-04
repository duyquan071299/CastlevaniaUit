#pragma once
#include"GameObject.h"
class CIntroObject
{
private:
	float x, y, vx, vy;

	LPANIMATION animation;
public:

	CIntroObject(){}
	CIntroObject(float x, float y, float vx, float vy, int Type)
	{
		if (Type == 0)
			animation = CAnimationDatabase::GetInstance()->Get(INTRO_BAT_ANI, ACTIVE);
		else
		{
			animation = new CAnimation(100);
			animation->Add(INTRO_OBJECT, 0, 0);
		}
		
		this->x = x;
		this->y = y;
		this->vx = vx;
		this->vy = vy;
		
	}

	void Render() {
		animation->Render(x, y, default_color);
	}

	void Update(DWORD dt)
	{
		x += vx * dt;
		y += vy * dt;
	}
	


};