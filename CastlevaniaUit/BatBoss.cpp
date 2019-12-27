#include"BatBoss.h"
#include"Simon.h"





CBatBoss::CBatBoss()
{


}




CBatBoss::CBatBoss(float x, float y)
{
	animations[SLEEP] = CAnimationDatabase::GetInstance()->Get(BOSS_ANI, SLEEP);
	animations[ACTIVE] = CAnimationDatabase::GetInstance()->Get(BOSS_ANI, ACTIVE);

	this->SetPosition(x, y);
	this->CurrentState = SLEEP;
	curAnimation = animations[SLEEP];
	Heal = 5;
	IsDead = false;

}

void CBatBoss::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects)
{
	if (Heal == 0)
	{
		this->IsDead = true;
	}
		
	if (isFrozen || IsDead )
		return;
	

		if (CurrentState == SLEEP)
		{
			vx = 0.0f;
			vy = 0.0f;
		}
		else if (CurrentState == ACTIVE)
		{
			if (MovingState == BEGIN_MOVE)
			{
				if (y >= LandingY)
				{
					
					vy = 0;
					PreviousX = x;
					PreviousY = y;

					AttackMovement();
					

					

				}
			}
			else if (MovingState == ATTACK_MOVE)
			{
				if (abs(x-x1)<abs(x3-x1) || (abs(y - y1) < abs(y3 - y1)))
				{
					perc += 0.01;
					int xa = getPt(x1, x2, perc);
					int ya = getPt(y1, y2, perc);
					int xb = getPt(x2, x3, perc);
					int yb = getPt(y2, y3, perc);
					int xc = getPt(xa, xb, perc);
					int yc = getPt(ya, yb, perc);
					vx = (xc - x) / (TIME_TO_NEXT_POINT);
					vy = (yc - y) / (TIME_TO_NEXT_POINT);
			
				
				}
				else
					AfterAttackMovement();

			}
			else if (MovingState == AFTER_ATTACK_MOVE)
			{
				if (y <= LandingY)
				{
					
					PreviousX = x;
					PreviousY = y;

					vx = 0;
					vy = 0;
					ReadyAttack();
				}
			}
			else if(MovingState == READY_ATTACK_MOVE)
			{
				if (y >= LandingY && !IsWaitTilNextMove)
				{

					PreviousX = x;
					PreviousY = y;
					vx = 0;
					vy = 0;

					StartWait();
				

				}
				if (GetTickCount() - TimeTilNextMove >= TIME_TILL_NEXT_MOVE && TimeTilNextMove != 0)
				{
					AttackMovement();
					TimeTilNextMove = 0;
					IsWaitTilNextMove = false;
				}
					
			}


		}
		CGameObject::Update(dt);
		x += dx;
		y += dy;
		


		if (x < CCamera::GetInstance()->GetBound().left || x + BOSS_WIDTH + 32 > CCamera::GetInstance()->GetBound().right || y < CCamera::GetInstance()->GetBound().top + 80 || y > CCamera::GetInstance()->GetBound().bottom)
			AfterAttackMovement();


	
}

void CBatBoss::Render()
{
	RenderBoundingBox();
	if (isFrozen && !isBurning)
	{
		curAnimation->SetCurrentFrame(curAnimation->GetCurrentFrame() - 1);
	}
	curAnimation->Render(x, y, default_color);
}

void CBatBoss::GetBoundingBox(float &x, float &y, float &framew, float &frameh)
{
	x = this->x;
	y = this->y;
	framew = BOSS_WIDTH;
	frameh = BOSS_HEIGHT;
}

void CBatBoss::StartMoving()
{
	int random = rand() % 2;
	SetCurrentState(ACTIVE);
	MovingState = BEGIN_MOVE;
	if (random == 0)
	{
		LandingY = y + rand() % (40 + 80);
		vx = 0.0f;
		vy = BOSS_BASE_SPEED;
		PreviousY = y;
	}
	else
	{
		if (CSimon::GetInstance()->x >= this->x)
		{
			LandingY = y + rand() % (RANDOM_DISTANCE_TO_SIMON + RANDOM_DISTANCE_TO_SIMON);
			LandingX = x - rand() % (RANDOM_DISTANCE_TO_SIMON + RANDOM_DISTANCE_TO_SIMON);
			vx = -BOSS_BASE_SPEED;
			
		}
		else
		{
			LandingY = y + rand() % (RANDOM_DISTANCE_TO_SIMON + RANDOM_DISTANCE_TO_SIMON);
			LandingX = x + rand() % (RANDOM_DISTANCE_TO_SIMON + RANDOM_DISTANCE_TO_SIMON);
			vx = BOSS_BASE_SPEED;
			
		}
		
	
		vy = BOSS_BASE_SPEED;
		PreviousY = y;
		PreviousY = x;
	}


}

void CBatBoss::AttackMovement()
{
	x1 = x;
	y1 = y;
	x2 = CSimon::GetInstance()->x;
	y2 = CSimon::GetInstance()->GetBBox().bottom;

	if (CSimon::GetInstance()->x >= this->x)
	{
		x3 = Random((int)(CSimon::GetInstance()->x + RANDOM_DISTANCE_TO_SIMON), (int)(CCamera::GetInstance()->GetBound().right));
	}
	else
	{

		x3 = Random((int)(CCamera::GetInstance()->GetBound().left), (int)(CSimon::GetInstance()->x - RANDOM_DISTANCE_TO_SIMON));
	}
	y3 = CSimon::GetInstance()->y - RANDOM_DISTANCE_TO_SIMON;
	perc = 0;
	MovingState = ATTACK_MOVE;
		
}

void CBatBoss::AfterAttackMovement()
{
	MovingState = AFTER_ATTACK_MOVE;
	PreviousX = x;
	PreviousY = y;
	LandingX = Random(AFTER_ATTACK_ZONE_X_LEFT, AFTER_ATTACK_ZONE_X_RIGHT);
	LandingY = Random(AFTER_ATTACK_ZONE_Y_TOP, AFTER_ATTACK_ZONE_Y_BOTTOM);
	vx = (LandingX - PreviousX) / (TIME_TOLCHECK_POINT);
	vy = (LandingY - PreviousY) / (TIME_TOLCHECK_POINT);
	
}


void CBatBoss::ReadyAttack()
{
	MovingState = READY_ATTACK_MOVE;
	PreviousX = x;
	PreviousY = y;
	LandingX = Random(ATTACK_ZONE_X_LEFT, ATTACK_ZONE_X_RIGHT);
	if (CSimon::GetInstance()->GetBBox().bottom < ATTACK_RANGE_1)
		LandingY = Random(ATTACK_ZONE_Y_1_TOP, ATTACK_ZONE_Y_1_BOTTOM);
	else if (CSimon::GetInstance()->GetBBox().bottom < ATTACK_RANGE_2)
		LandingY = Random(ATTACK_ZONE_Y_2_TOP, ATTACK_ZONE_Y_2_BOTTOM);
	else
		LandingY = Random(ATTACK_ZONE_Y_3_TOP, ATTACK_ZONE_Y_3_BOTTOM);

	vx = (LandingX - PreviousX) / (TIME_TOLCHECK_POINT);
	vy = (LandingY - PreviousY) / (TIME_TOLCHECK_POINT);
}

int CBatBoss::Random(int a, int b)
{
	return (rand() % (b - a)) + a;

}