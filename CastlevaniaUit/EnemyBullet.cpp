#include"EnemyBullet.h"

CEnemyBullet::CEnemyBullet()
{
	

}

CEnemyBullet::CEnemyBullet(float x, float y,int direction)
{
	animation = new CAnimation(100);
	this->x = x;
	this->y = y;
	ChangeAnimation(direction);

}


void CEnemyBullet::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects)
{
	if (this->IsDead == false)
	{

		CGameObject::Update(dt);
		if (isBurning)
			vx = 0;
		else
			vx = nx * ENEMY_BULLET_SPEED * dt;
		x += dx;
	

	}
}
void CEnemyBullet::ChangeAnimation(int index)
{
	delete animation;
	animation = new CAnimation(100);
	if (index == 1)
	{
		animation->Add(ENEMY, 19);
		nx = 1;
	}
	else
	{
		animation->Add(ENEMY, 18);
		nx = -1;
	}
	}
		
void CEnemyBullet::ChangeAnimation()
{
	this->isColiable = false;
	this->isBurning = true;
	LPANIMATION animation = new CAnimation(80);
	animation->Add(EFFECT, 0);
	animation->Add(EFFECT, 1);
	animation->Add(EFFECT, 2);
	this->animation = animation;
}
void CEnemyBullet::GetBoundingBox(float &x, float &y, float &framew, float &frameh)
{
	x = this->x;
	y = this->y;
	framew = 14;
	frameh = 12;
}
void CEnemyBullet::Render()
{
	if (isBurning)
	{
		animation->Render(x, y - 32, default_color);
		if (animation->IsLastFrame())
		{
			IsDead = true;
		}
	}
	else
	{
		animation->Render(x, y, default_color);
		RenderBoundingBox();
	}
	
}
