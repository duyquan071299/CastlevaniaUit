#pragma once
#include"Enemy.h"


class CBat :public CEnemy
{

public:
	CBat();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Respawn(int Direction)
	{
		if (Direction > 0)
			this->curAnimation = animations[WALKING_RIGHT];
		else
			this->curAnimation = animations[WALKING_LEFT];
	}
	~CBat() {}
	void ChangeAnimation();
	void Render()
	{
		if (curAnimation->IsLastFrame() == true && curAnimation->GetFrameSize() == 3 && isBurning)
		{
			IsDead = true;
			isColiable = false;
		}
		curAnimation->Render(x, y, default_color);
		RenderBoundingBox();
	}
	virtual void GetBoundingBox(float &x, float &y, float &framew, float &frameh);
};