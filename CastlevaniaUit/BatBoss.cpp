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

}

void CBatBoss::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects)
{
	if (CurrentState == SLEEP)
	{
		vx = 0.0f;
		vy = 0.0f;
	}
	else if(CurrentState==ACTIVE)
	{
		if (MovingState == 1)
		{
			if (y >= LandingY)
			{
				MovingState = 2;
				vy = 0;
				PreviousX = x;
				PreviousY = y;

				LandingX = 5480;
				LandingY = 300;

				vx = ((LandingX - PreviousX) / (1500.0f)); 
				vy = 0.15f;
			}
		}
		else if (MovingState == 2)
		{
			vy -= 0.0005f *dt;
			if (y<=LandingY && vy<0)
				vy = 0;
			if (x >= LandingX )
			{
				vx = 0;
				vy = 0;
			}
		}
		
			
	}
	CGameObject::Update(dt);
	x += dx;
	y += dy;
}

void CBatBoss::Render()
{
	RenderBoundingBox();
	animations[CurrentState]->Render(x, y, default_color);
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