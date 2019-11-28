#pragma once
#include"Enemy.h"
#include"EnemyBullet.h"
class CKappa :public CEnemy
{
private:
	State CurrentState;
	
	int KappaStep;

public:
	CKappa();
	CKappa(float x, float y, int direction);
	bool isOnGround;
	bool isWalking;
	bool isAtacking;
	bool isFire;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Respawn(int Direction)
	{
		this->nx = Direction;
		if (Direction > 0)
			this->curAnimation = animations[STANDING_RIGHT];
		else
			this->curAnimation = animations[STANDING_LEFT];
	}
	~CKappa() {}
	void ChangeAnimation();
	void Render()
	{
		
		curAnimation->Render(x, y, default_color);
		RenderBoundingBox();
	}
	virtual void GetBoundingBox(float &x, float &y, float &framew, float &frameh);
};