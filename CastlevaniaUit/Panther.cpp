#include"Panther.h"


CPanther::CPanther()
{
	
}

CPanther::CPanther(float x, float y, int Direction)
{
	
	animations[SITTING_LEFT] = CAnimationDatabase::GetInstance()->Get(PANTHER_ANI, SITTING_LEFT);
	animations[WALKING_LEFT] = CAnimationDatabase::GetInstance()->Get(PANTHER_ANI, WALKING_LEFT);
	animations[JUMPING_LEFT] = CAnimationDatabase::GetInstance()->Get(PANTHER_ANI, JUMPING_LEFT);
	animations[SITTING_RIGHT] = CAnimationDatabase::GetInstance()->Get(PANTHER_ANI, SITTING_RIGHT);
	animations[WALKING_RIGHT] = CAnimationDatabase::GetInstance()->Get(PANTHER_ANI, WALKING_RIGHT);
	animations[JUMPING_RIGHT] = CAnimationDatabase::GetInstance()->Get(PANTHER_ANI, JUMPING_RIGHT);


	isSitting = true;
	isRunning = false;
	isJumping = false;
	isOnground = false;
	isOnHigh = true;
	CountJump = 0;
	isFalling = false;
	isIncamera = true;
	IsDead = false;

	SetPosition(x, y);
	Respawn(Direction);
}

void CPanther::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects)
{
	if (isBurning == true)
	{
		if (curAnimation->IsLastFrame())
		{
			IsDead = true;
			isColiable = false;
		}
		return;
	}
	
	CGameObject::Update(dt);
	if (isBurning || isSitting)
		vx = 0;
	else if (isJumping)
	{
		vy = -0.4;
		isJumping = false;
		isFalling = true;
		if(direction>=0)
		{
			vx = 0.4;
			curAnimation = animations[JUMPING_RIGHT];
		}
		else
		{
			vx = -0.4;
			curAnimation = animations[JUMPING_LEFT];
		}
	}
	else if (isOnground && !isFalling)
	{
		if (direction > 0)
			vx = 0.3;
		else
			vx = -0.3;
	}
	else
	{
		if (direction > 0)
			vx = 0.3;
		else
			vx = -0.3;
	}


	
	if (vy == 0)
	{
		isOnground = true;
		isFalling = false;
		if (!isOnHigh && CountJump%2!=0)
		{
			CountJump += 1;
			direction = -direction;
		}
			
	}
	

	
	if (!isFrozen)
	{
		vy += GAME_GRAVITY * dt;
		CGameObject::Update(dt);
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

	
		if (dynamic_cast<CBrick *>(coEventsResult[0]->obj))
		{
			x += min_tx * dx + nx * 0.4f;		
			y += min_ty * dy + ny * 0.4f;

			if (isOnground&&!isSitting&&!isFalling)
			{
				isRunning = true;
				if (direction >= 0)
					curAnimation = animations[WALKING_RIGHT];
				else
					curAnimation = animations[WALKING_LEFT];
			}
				

			if (ny == 1)
			{
				y += dy;
			}

		}

		if (dynamic_cast<CInvisibleObject*>(coEventsResult[0]->obj))
		{
			CInvisibleObject*Object = dynamic_cast<CInvisibleObject *>(coEventsResult[0]->obj);
			if (Object->GetType() == 3)
			{
				isSitting = false;
				isRunning = false;
				isJumping = true;
				isOnHigh = false;
				CountJump += 1;
			}
		

		}

		if (nx != 0) vx = 0;
		if (ny == -1) vy = 0;
	}
}

void  CPanther::GetBoundingBox(float &x, float &y, float &framew, float &frameh)
{
	if (isSitting)
	{
		x = this->x;
		y = this->y+2;
		framew = 48;
		frameh = 30;
	}
	else if (isRunning)
	{
		x = this->x;
		y = this->y;
		framew = 60;
		frameh = 26;
	}
	else if (isJumping)
	{
		x = this->x;
		y = this->y;
		framew = 64;
		frameh = 26;
	}
	else
	{
		x = this->x;
		y = this->y;
		framew = 64;
		frameh = 26;
	}
	


}

void CPanther::ChangeAnimation()
{
	this->isColiable = false;
	this->isBurning = true;
	vx = 0;
	LPANIMATION animation = new CAnimation(80);
	animation->Add(EFFECT, 0);
	animation->Add(EFFECT, 1);
	animation->Add(EFFECT, 2);
	this->curAnimation = animation;

}