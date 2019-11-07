#include"Ghost.h"


CGhost::CGhost()
{
	LPANIMATION ani = new CAnimation(100);
	ani->Add(ENEMY, 0);
	ani->Add(ENEMY, 1);
	animations[WALKING_LEFT] = ani;
	ani = new CAnimation(100);
	ani->Add(ENEMY, 2);
	ani->Add(ENEMY, 3);
	animations[WALKING_RIGHT] = ani;

}

void CGhost::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects)
{
	CGameObject::Update(dt);
	if (isBurning)
		vx = 0;
	else
		vx = -0.05;
	vy += GAME_GRAVITY * dt;
	CGameObject::Update(dt);



	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(colliable_objects, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
			
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;
		
		
		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
	}
}

void  CGhost::GetBoundingBox(float &x, float &y, float &framew, float &frameh)
{

	x = this->x;
	y = this->y;
	framew = 32;
	frameh = 64;


}

void CGhost::ChangeAnimation()
{
	this->isColiable = false;
	this->isBurning = true;
	LPANIMATION animation = new CAnimation(80);
	animation->Add(EFFECT, 0);
	animation->Add(EFFECT, 1);
	animation->Add(EFFECT, 2);
	this->curAnimation = animation;

}