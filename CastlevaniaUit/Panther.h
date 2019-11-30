#pragma once
#include"Enemy.h"
#include"Brick.h"
#include"InvisibleObject.h"
class CPanther :public CEnemy
{
protected:

public:
	CPanther();
	CPanther(float x, float y, int Direction);
	bool isSitting;
	bool isRunning;
	bool isJumping;
	bool isOnground;
	bool isOnHigh;
	int CountJump;
	bool isFalling;
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
		}
		else
		{
			curAnimation->Render(x, y, default_color);
			RenderBoundingBox();
		}
			
		
		
		
	}
	virtual void GetBoundingBox(float &x, float &y, float &framew, float &frameh);
};