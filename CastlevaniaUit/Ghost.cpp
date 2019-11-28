#include"Ghost.h"
#include"Brick.h"
#include"Camera.h"

CGhost::CGhost()
{
	
}

CGhost::CGhost(float fx, float fy, int direction)
{
	LPANIMATION ani = new CAnimation(100);
	ani->Add(ENEMY, 0);
	ani->Add(ENEMY, 1);
	animations[WALKING_LEFT] = ani;
	ani = new CAnimation(100);
	ani->Add(ENEMY, 2);
	ani->Add(ENEMY, 3);
	animations[WALKING_RIGHT] = ani;
	SetPosition(fx, fy);
	Respawn(direction);
	isIncamera = true;
}

void CGhost::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects)
{
	
	CGameObject::Update(dt);
	if (isBurning)
	{
		vx = 0;
		vy += GAME_GRAVITY * dt;
	}
		
	else if(isFrozen)
	{
		vx = 0;
		vy = 0;
	}
	else
	{
		if (nx > 0)
			vx = 0.1;
		else
			vx = -0.1;
		vy += GAME_GRAVITY * dt;
	}
		
	

	if (CCamera::GetInstance()->x == (float)3072 - CCamera::GetInstance()->GetWidth() + 16)
	{
		if (this->nx == -1 && this->x < CCamera::GetInstance()->x )
		{
			Respawn(1);
		}
	}

	if (curAnimation->IsLastFrame() == true && curAnimation->GetFrameSize() == 3)
	{
		IsDead = true;
		isColiable = false;
	}
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
		if (dynamic_cast<CBrick *>(coEventsResult[0]->obj))
		{
			x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
			y += min_ty * dy + ny * 0.4f;
		}
		
		
		
		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrick *>(e->obj))
			{
				if (dynamic_cast<CBrick *>(e->obj)->GetType() == 2)
				{
					Respawn(-this->nx);
				}
			}
		}
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