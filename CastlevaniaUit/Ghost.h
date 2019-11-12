#pragma once
#include"Enemy.h"
#include"Brick.h"

class CGhost :public CEnemy
{

public:
	CGhost();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Respawn(int Direction)
	{
		if (Direction > 0)
			this->curAnimation = animations[WALKING_RIGHT];
		else
			this->curAnimation = animations[WALKING_LEFT];
	}
	~CGhost() {}
	void ChangeAnimation();
	void Render()
	{
		if (curAnimation->IsLastFrame() == true && curAnimation->GetFrameSize() == 3)
		{
			IsDead = true;
			isColiable = false;
		}
		curAnimation->Render(x,y,default_color);
		RenderBoundingBox();
	}
	virtual void GetBoundingBox(float &x, float &y, float &framew, float &frameh);
};