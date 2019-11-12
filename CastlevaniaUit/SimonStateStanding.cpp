#include"SimonStateStanding.h"
#include"SimonStateSitting.h"
#include"SimonStateWalkingOnStair.h"

void CSimonStateStanding::Update(DWORD dt)
{
	if (CSimon::GetInstance()->IsOnAnimation)
	{
		if (CSimon::GetInstance()->x > CSimon::GetInstance()->CheckPoint)
		{
			CSimon::GetInstance()->SetCurrentAnimation(WALKING_LEFT);
			CSimon::GetInstance()->vx = -0.1;
		}
		else
		{
			CSimon::GetInstance()->SetCurrentAnimation(WALKING_RIGHT);
			CSimon::GetInstance()->vx = 0.1;
		}
			
		
		if (abs(CSimon::GetInstance()->x - CSimon::GetInstance()->CheckPoint) <= 1.5)
		{
			if (CSimon::GetInstance()->isUP)
			{
				CSimon::GetInstance()->x = CSimon::GetInstance()->CheckPoint;
				if (CSimon::GetInstance()->DirectionStair == 1)
				{
					CSimon::GetInstance()->vx = SIMON_ONSTAIR_SPEED * CSimon::GetInstance()->DirectionStair;
					CSimon::GetInstance()->vy = -SIMON_ONSTAIR_SPEED;
					CSimon::GetInstance()->ChangeState(new CSimonStateWalkingOnStair(ONSTAIR_WALKING_UP_RIGHT));
					CSimon::GetInstance()->isUP = true;
				}
				else if (CSimon::GetInstance()->DirectionStair == -1)
				{
					CSimon::GetInstance()->vx = SIMON_ONSTAIR_SPEED * CSimon::GetInstance()->DirectionStair;
					CSimon::GetInstance()->vy = -SIMON_ONSTAIR_SPEED;
					CSimon::GetInstance()->ChangeState(new CSimonStateWalkingOnStair(ONSTAIR_WALKING_UP_LEFT));
					CSimon::GetInstance()->isUP = true;
				}
			}
			else
			{
				
				if (CSimon::GetInstance()->DirectionStair == 1)
				{
					CSimon::GetInstance()->x = CSimon::GetInstance()->CheckPoint;
					CSimon::GetInstance()->vx = SIMON_ONSTAIR_SPEED * (-CSimon::GetInstance()->DirectionStair);
					CSimon::GetInstance()->vy = SIMON_ONSTAIR_SPEED;
					CSimon::GetInstance()->ChangeState(new CSimonStateWalkingOnStair(ONSTAIR_WALKING_DOWN_LEFT));
					CSimon::GetInstance()->isUP = false;
				}
				else if (CSimon::GetInstance()->DirectionStair == -1)
				{
					CSimon::GetInstance()->x = CSimon::GetInstance()->CheckPoint;
					CSimon::GetInstance()->vx = SIMON_ONSTAIR_SPEED * (-CSimon::GetInstance()->DirectionStair);
					CSimon::GetInstance()->vy = SIMON_ONSTAIR_SPEED;
					CSimon::GetInstance()->ChangeState(new CSimonStateWalkingOnStair(ONSTAIR_WALKING_DOWN_RIGHT));
					CSimon::GetInstance()->isUP = false;
				}
			}
			CSimon::GetInstance()->isOnStair = true;

		}
	}
		
}
void CSimonStateStanding::HandleKeyboard(unordered_map<int, bool> keyCode)
{
	if (keyCode[DIK_RIGHT]&& !keyCode[DIK_LEFT])
	{
		if (CSimon::GetInstance()->isOnStair == true)
		{
			if (CSimon::GetInstance()->DirectionStair == 1)
			{

				CSimon::GetInstance()->ChangeState(new CSimonStateWalkingOnStair(ONSTAIR_WALKING_UP_RIGHT));
				CSimon::GetInstance()->isUP = true;
			}
			else
			{
				CSimon::GetInstance()->ChangeState(new CSimonStateWalkingOnStair(ONSTAIR_WALKING_DOWN_RIGHT));
				CSimon::GetInstance()->isUP = false;
			}
			
		}
		else
		{
			CSimon::GetInstance()->ChangeState(new CSimonStateWalking(WALKING_RIGHT));
			
		}
		CSimon::GetInstance()->nx = 1;
	
	}
	else if(keyCode[DIK_LEFT]&& !keyCode[DIK_RIGHT])
	{
		if (CSimon::GetInstance()->isOnStair == true)
		{
			if (CSimon::GetInstance()->DirectionStair == 1)
			{
				CSimon::GetInstance()->ChangeState(new CSimonStateWalkingOnStair(ONSTAIR_WALKING_UP_LEFT));
				CSimon::GetInstance()->isUP = true;
			}
			else
			{
				CSimon::GetInstance()->ChangeState(new CSimonStateWalkingOnStair(ONSTAIR_WALKING_DOWN_LEFT));
				CSimon::GetInstance()->isUP = false;
			}
				
		}
		else
			CSimon::GetInstance()->ChangeState(new CSimonStateWalking(WALKING_LEFT));
		CSimon::GetInstance()->nx = -1;

	}
	else if (keyCode[DIK_DOWN]&& !keyCode[DIK_UP])
	{
		
		if (CSimon::GetInstance()->isOnStair == true)
		{
			if (CSimon::GetInstance()->DirectionStair == 1)
				CSimon::GetInstance()->ChangeState(new CSimonStateWalkingOnStair(ONSTAIR_WALKING_DOWN_LEFT));
			else
				CSimon::GetInstance()->ChangeState(new CSimonStateWalkingOnStair(ONSTAIR_WALKING_DOWN_RIGHT));
			CSimon::GetInstance()->isUP = false;
		}
		else if (CSimon::GetInstance()->isColiableWithStairTop)
		{
			if (abs(CSimon::GetInstance()->x - CSimon::GetInstance()->CheckPoint) > 0.5)
			{
				CSimon::GetInstance()->IsOnAnimation = true;
				CSimon::GetInstance()->isUP = false;
			}
			else
			{
				
				if (CSimon::GetInstance()->DirectionStair == 1)
				{
					CSimon::GetInstance()->x = CSimon::GetInstance()->CheckPoint;
					CSimon::GetInstance()->vx = SIMON_ONSTAIR_SPEED * (-CSimon::GetInstance()->DirectionStair);
					CSimon::GetInstance()->vy = SIMON_ONSTAIR_SPEED;
					CSimon::GetInstance()->ChangeState(new CSimonStateWalkingOnStair(ONSTAIR_WALKING_DOWN_LEFT));
					CSimon::GetInstance()->isUP = false;
				}
				else if (CSimon::GetInstance()->DirectionStair == -1)
				{
					CSimon::GetInstance()->x = CSimon::GetInstance()->CheckPoint-5;
					CSimon::GetInstance()->vx = SIMON_ONSTAIR_SPEED * (-CSimon::GetInstance()->DirectionStair);
					CSimon::GetInstance()->vy = SIMON_ONSTAIR_SPEED;
					CSimon::GetInstance()->ChangeState(new CSimonStateWalkingOnStair(ONSTAIR_WALKING_DOWN_RIGHT));
					CSimon::GetInstance()->isUP = false;
				}

				CSimon::GetInstance()->isOnStair = true;
			}
		}
		else
		{
			if (CSimon::GetInstance()->nx > 0)
				CSimon::GetInstance()->ChangeState(new CSimonStateSitting(SITTING_RIGHT));
			else
				CSimon::GetInstance()->ChangeState(new CSimonStateSitting(SITTING_LEFT));
			CSimon::GetInstance()->vx = 0;
		}
	
	}
	else if (keyCode[DIK_UP])
	{

		if (CSimon::GetInstance()->isOnStair)
		{
			if (CSimon::GetInstance()->DirectionStair == 1)
			{
				CSimon::GetInstance()->ChangeState(new CSimonStateWalkingOnStair(ONSTAIR_WALKING_UP_RIGHT));
				CSimon::GetInstance()->isUP = true;
			}
			else
			{
				CSimon::GetInstance()->ChangeState(new CSimonStateWalkingOnStair(ONSTAIR_WALKING_UP_LEFT));
				CSimon::GetInstance()->isUP = true;
			}

				
		}
		else if(CSimon::GetInstance()->isColiableWithStairBottom)
		{
			if (abs(CSimon::GetInstance()->x - CSimon::GetInstance()->CheckPoint) > 1.5)
			{
				CSimon::GetInstance()->IsOnAnimation = true;
				CSimon::GetInstance()->isUP = true;
			}	
			else
			{
				CSimon::GetInstance()->x = CSimon::GetInstance()->CheckPoint;
				if (CSimon::GetInstance()->DirectionStair == 1)
				{
					CSimon::GetInstance()->vx = SIMON_ONSTAIR_SPEED * CSimon::GetInstance()->DirectionStair;
					CSimon::GetInstance()->vy = -SIMON_ONSTAIR_SPEED;
					CSimon::GetInstance()->ChangeState(new CSimonStateWalkingOnStair(ONSTAIR_WALKING_UP_RIGHT));
					CSimon::GetInstance()->isUP = true;
				}
				else if (CSimon::GetInstance()->DirectionStair == -1)
				{
					CSimon::GetInstance()->vx = SIMON_ONSTAIR_SPEED * CSimon::GetInstance()->DirectionStair;
					CSimon::GetInstance()->vy = -SIMON_ONSTAIR_SPEED;
					CSimon::GetInstance()->ChangeState(new CSimonStateWalkingOnStair(ONSTAIR_WALKING_UP_LEFT));
					CSimon::GetInstance()->isUP = true;
				}

				CSimon::GetInstance()->isOnStair = true;
			}
			
			
		}
			
	}

}

void CSimonStateStanding::Exit()
{
	CSimon::GetInstance()->IsStanding = false;
}
void CSimonStateStanding::Enter()
{
	CSimon::GetInstance()->vx = 0;
	CSimon::GetInstance()->vy = 0;
	CSimon::GetInstance()->IsStanding = true;
	CSimon::GetInstance()->IsOnAir = false;

}