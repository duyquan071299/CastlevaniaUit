#pragma once
#include"Enemy.h"
#include"Brick.h"
#include"InvisibleObject.h"
class CPanther :public CEnemy
{
protected:

public:
	CPanther();
	bool isBurning = false;
	bool isSitting = true;
	bool isRunning = false;
	bool isJumping = false;
	bool isOnground = false;
	bool isOnHigh = true;
	bool isChange = false;
	bool isFalling = false;
	int direction;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Respawn(int Direction)
	{
		direction = Direction;
		if (Direction > 0)
			this->curAnimation = animations[SITTING_RIGHT];
		else
			this->curAnimation = animations[SITTING_LEFT];
	}
	void ChangeAni()
	{
		this->curAnimation = animations[WALKING_LEFT];
	}
	~CPanther() {}
	void ChangeAnimation();
	void Render()
	{
		if (isBurning)
		{
			curAnimation->Render(x, y-16, default_color);
			if (curAnimation->IsLastFrame())
			{
				IsDead = true;
				isColiable = false;
			}
		}
		else
		{
			curAnimation->Render(x, y, default_color);
			RenderBoundingBox();
		}
			
		
		
		
	}
	virtual void GetBoundingBox(float &x, float &y, float &framew, float &frameh);
};