#pragma once
#include"Enemy.h"
#include"Brick.h"

class CGhost :public CEnemy
{

public:
	CGhost();
	CGhost(float x, float y, int direction);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Respawn(int Direction)
	{
		this->nx = Direction;
		if (Direction > 0)
			this->curAnimation = animations[WALKING_RIGHT];
		else
			this->curAnimation = animations[WALKING_LEFT];
	}
	~CGhost() {}
	void ChangeAnimation();
	void Render()
	{
		if (isFrozen && !isBurning)
		{
			curAnimation->SetCurrentFrame(curAnimation->GetCurrentFrame()- 1);
		}
		curAnimation->Render(x, y, default_color);
		RenderBoundingBox();
	}
	virtual void GetBoundingBox(float &x, float &y, float &framew, float &frameh);
};