#include"Bat.h"


CBat::CBat()
{


}
CBat::CBat(float x, float y, int direction)
{

	animations[WALKING_LEFT] = CAnimationDatabase::GetInstance()->Get(BAT_ANI, WALKING_LEFT);
	animations[WALKING_RIGHT] = CAnimationDatabase::GetInstance()->Get(BAT_ANI, WALKING_RIGHT);

	SetPosition(x, y);
	Respawn(direction);
	isIncamera = true;
}

void CBat::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects)
{
	if (nx > 0)
		vx = 0.01f*dt;
	else
		vx = -0.01f* dt;
	CGameObject::Update(dt);
	if (isBurning)
	{
		vx = 0;
		vy = 0;
		if (curAnimation->IsLastFrame() == true && curAnimation->GetFrameSize() == 3 )
		{
			IsDead = true;
			isColiable = false;
		}
	}
	else if (isFrozen)
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