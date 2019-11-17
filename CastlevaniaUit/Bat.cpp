#include"Bat.h"


CBat::CBat()
{
	LPANIMATION ani = new CAnimation(200);
	ani->Add(ENEMY, 20);
	ani->Add(ENEMY, 21);
	ani->Add(ENEMY, 22);
	animations[WALKING_LEFT] = ani;
	ani = new CAnimation(200);
	ani->Add(ENEMY, 23);
	ani->Add(ENEMY, 24);
	ani->Add(ENEMY, 25);
	animations[WALKING_RIGHT] = ani;
	this->curAnimation = animations[WALKING_LEFT];

}

void CBat::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects)
{

	vx = -0.008* dt;
	CGameObject::Update(dt);
	if (isBurning)
	{
		vx = 0;
		vy = 0;
	}
	else
	{
		x += dx;
		y += -1*sin((x) / 30);
	}
	

	

}

void  CBat::GetBoundingBox(float &x, float &y, float &framew, float &frameh)
{

	x = this->x;
	y = this->y;
	framew = 32;
	frameh = 32;


}

void CBat::ChangeAnimation()
{
	this->isColiable = false;
	this->isBurning = true;
	LPANIMATION animation = new CAnimation(80);
	animation->Add(EFFECT, 0);
	animation->Add(EFFECT, 1);
	animation->Add(EFFECT, 2);
	this->curAnimation = animation;

}