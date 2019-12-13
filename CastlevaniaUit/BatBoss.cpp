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
	Heal = 16;

}

void CBatBoss::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects)
{
	if (isFrozen )
		return;

		if (CurrentState == SLEEP)
		{
			vx = 0.0f;
			vy = 0.0f;
		}
		else if (CurrentState == ACTIVE)
		{
			if (MovingState == 1)
			{
				if (y >= LandingY)
				{
					
					vy = 0;
					PreviousX = x;
					PreviousY = y;

					AttackMovement();

					vx = 0;
					vy = 0;

				}
			}
			else if (MovingState == 2)
			{
				if (perc < 1)
				{
					perc += 0.01;
					int xa = getPt(x1, x2, perc);
					int ya = getPt(y1, y2, perc);
					int xb = getPt(x2, x3, perc);
					int yb = getPt(y2, y3, perc);

					x = getPt(xa, xb, perc);
					y = getPt(ya, yb, perc);
				}
				else
					AfterAttackMovement();

			}
			else if (MovingState == 3)
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
			else if(MovingState == 4)
			{
				if (y >= LandingY && !IsWaitTilNextMove)
				{

					PreviousX = x;
					PreviousY = y;


					vx = 0;
					vy = 0;

					StartWait();
				

				}
				if (GetTickCount() - TimeTilNextMove >= 2000 && TimeTilNextMove != 0)
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
		


		if (x < CCamera::GetInstance()->GetBound().left || x + BOSS_WIDTH + 32 > CCamera::GetInstance()->GetBound().right || y < CCamera::GetInstance()->GetBound().top - 80 || y > CCamera::GetInstance()->GetBound().bottom)
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
	MovingState = 1;
	if (random == 0)
	{
		LandingY = y + rand() % (40 + 80);
		vx = 0.0f;
		vy = 0.05f;
		PreviousY = y;
	}
	else
	{
		if (CSimon::GetInstance()->x >= this->x)
		{
			LandingY = y + rand() % (100 + 100);
			LandingX = x - rand() % (100 + 100);
			vx = -0.05f;
			
		}
		else
		{
			LandingY = y + rand() % (100 + 100);
			LandingX = x + rand() % (100 + 100);
			vx = 0.05f;
			
		}
		
	
		vy = 0.05f;
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
		x3 = Random((int)(CSimon::GetInstance()->x + 100), (int)(CCamera::GetInstance()->GetBound().right));
	}
	else
	{

		x3 = Random((int)(CCamera::GetInstance()->GetBound().left), (int)(CSimon::GetInstance()->x - 100));
	}
	y3 = CSimon::GetInstance()->y - 100;
	perc = 0;
	MovingState = 2;
		
}

void CBatBoss::AfterAttackMovement()
{
	MovingState = 3;
	PreviousX = x;
	PreviousY = y;
	LandingX = Random(AFTER_ATTACK_ZONE_X_LEFT, AFTER_ATTACK_ZONE_X_RIGHT);
	LandingY = Random(AFTER_ATTACK_ZONE_Y_TOP, AFTER_ATTACK_ZONE_Y_BOTTOM);
	vx = (LandingX - PreviousX) / (1500);
	vy = (LandingY - PreviousY) / (1500);
	
}


void CBatBoss::ReadyAttack()
{
	MovingState = 4;
	PreviousX = x;
	PreviousY = y;
	LandingX = Random(ATTACK_ZONE_X_LEFT, ATTACK_ZONE_X_RIGHT);
	if (CSimon::GetInstance()->GetBBox().bottom < 340)
		LandingY = Random(ATTACK_ZONE_Y_1_TOP, ATTACK_ZONE_Y_1_BOTTOM);
	else if (CSimon::GetInstance()->GetBBox().bottom < 265)
		LandingY = Random(ATTACK_ZONE_Y_2_TOP, ATTACK_ZONE_Y_2_BOTTOM);
	else
		LandingY = Random(ATTACK_ZONE_Y_3_TOP, ATTACK_ZONE_Y_3_BOTTOM);

	vx = (LandingX - PreviousX) / (1500);
	vy = (LandingY - PreviousY) / (1500);
}

int CBatBoss::Random(int a, int b)
{
	return (rand() % (b - a)) + a;

}