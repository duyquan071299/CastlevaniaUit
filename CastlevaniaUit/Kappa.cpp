#include"Kappa.h"
#include"Simon.h"
CKappa::CKappa()
{
	
	

}

CKappa::CKappa(float x, float y, int direction)
{
	LPANIMATION ani = new CAnimation(500);
	ani->Add(ENEMY, 5);
	ani->Add(ENEMY, 6);
	animations[WALKING_LEFT] = ani;

	ani = new CAnimation(100);
	ani->Add(ENEMY, 5);
	animations[STANDING_LEFT] = ani;

	ani = new CAnimation(500);
	ani->Add(ENEMY, 8);
	ani->Add(ENEMY, 9);
	animations[WALKING_RIGHT] = ani;

	ani = new CAnimation(100);
	ani->Add(ENEMY, 8);
	animations[STANDING_RIGHT] = ani;

	ani = new CAnimation(500);
	ani->Add(ENEMY, 4);
	animations[ATTACKING_STAND_LEFT] = ani;

	ani = new CAnimation(500);
	ani->Add(ENEMY, 7);
	animations[ATTACKING_STAND_RIGHT] = ani;

	this->vy = -0.7;
	this->isOnGround = false;
	this->isFire = false;
	this->IsDead = false;
	this->isIncamera = true;
	SetPosition(x, y);
	Respawn(direction);
}

void CKappa::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects)
{
	CGameObject::Update(dt);
	if (isBurning)
	{
		isWalking = false;
		vx = 0;
	}
	else if (isOnGround && !isAtacking)
	{
		isWalking = true;
		isAtacking = false;
		if (nx > 0)
		{
			CurrentState = WALKING_RIGHT;
			vx = 0.05;
		}
		else
		{
			CurrentState = WALKING_LEFT;
			vx = -0.05;
		}
		
		
		curAnimation = animations[CurrentState];
	}
	else if(isAtacking)
	{
		isWalking = false;
		vx = 0;
		if (nx > 0)
			CurrentState = ATTACKING_STAND_RIGHT;
		else
			CurrentState = ATTACKING_STAND_LEFT;
		curAnimation = animations[CurrentState];
		
	}

	if (isAtacking && curAnimation->IsLastFrame())
	{
		isAtacking = false;
		if (CSimon::GetInstance()->y > y-1.5 )
		{
			if (CSimon::GetInstance()->x > x && nx > 0)
				nx = nx;
			else if (CSimon::GetInstance()->x > x && nx < 0)
				nx = -nx;
			else if (CSimon::GetInstance()->x < x && nx > 0)
				nx = -nx;
			else if (CSimon::GetInstance()->x < x && nx < 0)
				nx = nx;
		}
		else
			nx = -nx;
		curAnimation->SetIsLastFrame(false);
		KappaStep = 0;
		isFire = false;

	
	}

	if (isWalking && curAnimation->IsLastFrame())
	{
		curAnimation->SetIsLastFrame(false);
		KappaStep += 1;
		
	}

	if (curAnimation->IsLastFrame() == true && curAnimation->GetFrameSize() == 3)
	{
		IsDead = true;
		isColiable = false;
	}



	if (KappaStep == 2)
	{
		isAtacking = true;

	}
	


	vy += 0.001 * dt;




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

		if (dynamic_cast<CBrick *>(coEventsResult[0]->obj))
		{
			x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
			y += min_ty * dy + ny * 0.4f;
		}



		if (ny == 1)
		{
			y += dy;
		}

		if (nx != 0)
			x += dx;

		if (nx != 0) vx = 0;
		if (ny == -1) vy = 0;



		if (vy == 0)
		{
			this->isOnGround = true;
		}


	}
}

void  CKappa::GetBoundingBox(float &x, float &y, float &framew, float &frameh)
{
	if (!this->isOnGround)
	{
		x = this->x+16;
		y = this->y + 5;
		framew = 2;
		frameh = 59;
	}
	else
	{
		x = this->x;
		y = this->y + 5;
		framew = 32;
		frameh = 59;
	}



}

void CKappa::ChangeAnimation()
{
	this->isColiable = false;
	this->isBurning = true;
	LPANIMATION animation = new CAnimation(80);
	animation->Add(EFFECT, 0);
	animation->Add(EFFECT, 1);
	animation->Add(EFFECT, 2);
	this->curAnimation = animation;

}