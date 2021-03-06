#include"SimonStateWalkingOnStair.h"


void CSimonStateWalkingOnStair::Update(DWORD dt)
{
	if (CSimon::GetInstance()->IsOnAnimation)
	{
		if (CSimon::GetInstance()->DirectionStair == 1)
		{
			if (CSimon::GetInstance()->x > CSimon::GetInstance()->CheckPoint+15  && CSimon::GetInstance()->isUP)
			{
				CSimon::GetInstance()->getCurrentAnimation()->SetIsLastFrame(true);
				CSimon::GetInstance()->isWalkingInOutGround = false;
				CSimon::GetInstance()->IsOnAnimation = false;
			}
			
			else if (CSimon::GetInstance()->x < CSimon::GetInstance()->CheckPoint - 17 && !CSimon::GetInstance()->isUP)
			{
				CSimon::GetInstance()->getCurrentAnimation()->SetIsLastFrame(true);
				CSimon::GetInstance()->isWalkingInOutGround = false;
				CSimon::GetInstance()->IsOnAnimation = false;
			}
				
		}
		else
		{
		

			if (CSimon::GetInstance()->x < CSimon::GetInstance()->CheckPoint -16&& CSimon::GetInstance()->isUP)
			{
				CSimon::GetInstance()->IsOnAnimation = false;
				CSimon::GetInstance()->isWalkingInOutGround = false;
				CSimon::GetInstance()->getCurrentAnimation()->SetIsLastFrame(true);
			}
				
			else if (CSimon::GetInstance()->x > CSimon::GetInstance()->CheckPoint + 10 && !CSimon::GetInstance()->isUP)
			{
				CSimon::GetInstance()->IsOnAnimation = false;
				CSimon::GetInstance()->isWalkingInOutGround = false;
				CSimon::GetInstance()->getCurrentAnimation()->SetIsLastFrame(true);


			}
				
		}
		
		if (!CSimon::GetInstance()->IsOnAnimation)
		{
			CSimon::GetInstance()->PreviousX = CSimon::GetInstance()->x;
			CSimon::GetInstance()->PreviousY = CSimon::GetInstance()->y;
		}


	}
	else
	{
		if (CSimon::GetInstance()->DirectionStair == 1)
		{
			if (CSimon::GetInstance()->y - CSimon::GetInstance()->PreviousY >= 16 && CSimon::GetInstance()->PreviousX - CSimon::GetInstance()->x >= 16)
			{
				if (CSimon::GetInstance()->PreviousX - CSimon::GetInstance()->x > 16)
				{
					CSimon::GetInstance()->x = CSimon::GetInstance()->PreviousX - 16;
				}
				if (CSimon::GetInstance()->y - CSimon::GetInstance()->PreviousY > 16)
				{
					CSimon::GetInstance()->y = CSimon::GetInstance()->PreviousY + 16;
				}
				CSimon::GetInstance()->PreviousX = CSimon::GetInstance()->x;
				CSimon::GetInstance()->PreviousY = CSimon::GetInstance()->y;

				CSimon::GetInstance()->getCurrentAnimation()->SetIsLastFrame(true);

			}
			else if (CSimon::GetInstance()->PreviousY - CSimon::GetInstance()->y >= 16 && CSimon::GetInstance()->x - CSimon::GetInstance()->PreviousX >= 16)
			{
				if (CSimon::GetInstance()->PreviousY - CSimon::GetInstance()->y > 16)
				{
					CSimon::GetInstance()->y = CSimon::GetInstance()->PreviousY - 16;
				}
				if (CSimon::GetInstance()->x - CSimon::GetInstance()->PreviousX > 16)
				{
					CSimon::GetInstance()->x = CSimon::GetInstance()->PreviousX + 16;
				}
				CSimon::GetInstance()->PreviousX = CSimon::GetInstance()->x;
				CSimon::GetInstance()->PreviousY = CSimon::GetInstance()->y;

				CSimon::GetInstance()->getCurrentAnimation()->SetIsLastFrame(true);
			}
		}
		else
		{
			if (CSimon::GetInstance()->x - CSimon::GetInstance()->PreviousX >= 16 && CSimon::GetInstance()->y - CSimon::GetInstance()->PreviousY >= 16)
			{
				if (CSimon::GetInstance()->x - CSimon::GetInstance()->PreviousX > 16)
				{
					CSimon::GetInstance()->x = CSimon::GetInstance()->PreviousX + 16;
				}
				if (CSimon::GetInstance()->y - CSimon::GetInstance()->PreviousY > 16)
				{
					CSimon::GetInstance()->y = CSimon::GetInstance()->PreviousY + 16;
				}
				CSimon::GetInstance()->PreviousX = CSimon::GetInstance()->x;
				CSimon::GetInstance()->PreviousY = CSimon::GetInstance()->y;

				CSimon::GetInstance()->getCurrentAnimation()->SetIsLastFrame(true);

			}
			else if (CSimon::GetInstance()->PreviousY - CSimon::GetInstance()->y >= 16 && CSimon::GetInstance()->PreviousX - CSimon::GetInstance()->x >= 16)
			{
				if (CSimon::GetInstance()->PreviousY - CSimon::GetInstance()->y > 16)
				{
					CSimon::GetInstance()->y = CSimon::GetInstance()->PreviousY - 16;
				}
				if (CSimon::GetInstance()->PreviousX - CSimon::GetInstance()->x> 16)
				{
					CSimon::GetInstance()->x = CSimon::GetInstance()->PreviousX - 16;
				}
				CSimon::GetInstance()->PreviousX = CSimon::GetInstance()->x;
				CSimon::GetInstance()->PreviousY = CSimon::GetInstance()->y;

				CSimon::GetInstance()->getCurrentAnimation()->SetIsLastFrame(true);
			}
		}
		
	}

}
	



void CSimonStateWalkingOnStair::HandleKeyboard(unordered_map<int, bool> keyCode)
{
	if (keyCode[DIK_RIGHT])
	{
		CSimon::GetInstance()->nx = 1;
		if (keyCode[DIK_LEFT])
		{
			/*if (CSimon::GetInstance()->nx > 0)
				CSimon::GetInstance()->ChangeState(new CSimonStateStanding(ONSTAIR_STANDING_RIGHT));
			else
				CSimon::GetInstance()->ChangeState(new CSimonStateStanding(ONSTAIR_STANDING_LEFT));
			return;*/
		}
		if (CSimon::GetInstance()->DirectionStair == 1)
		{
			CSimon::GetInstance()->vx = SIMON_ONSTAIR_SPEED * CSimon::GetInstance()->DirectionStair;
			CSimon::GetInstance()->vy = -SIMON_ONSTAIR_SPEED;
			CSimon::GetInstance()->isUP = true;
			CSimon::GetInstance()->SetCurrentAnimation(ONSTAIR_WALKING_UP_RIGHT);
	
			
		}
		else
		{
			CSimon::GetInstance()->vx = SIMON_ONSTAIR_SPEED * (-CSimon::GetInstance()->DirectionStair);
			CSimon::GetInstance()->vy = SIMON_ONSTAIR_SPEED;
			CSimon::GetInstance()->isUP = false;
			CSimon::GetInstance()->SetCurrentAnimation(ONSTAIR_WALKING_DOWN_RIGHT);
		}
		
			
			
	}
	else if (keyCode[DIK_LEFT])
	{
		CSimon::GetInstance()->nx = -1;

		if (CSimon::GetInstance()->DirectionStair == 1)
		{
			CSimon::GetInstance()->vx = SIMON_ONSTAIR_SPEED * (-CSimon::GetInstance()->DirectionStair);
			CSimon::GetInstance()->vy = SIMON_ONSTAIR_SPEED;
			CSimon::GetInstance()->isUP =false;
			CSimon::GetInstance()->SetCurrentAnimation(ONSTAIR_WALKING_DOWN_LEFT);
		}
		else
		{
			CSimon::GetInstance()->vx = SIMON_ONSTAIR_SPEED * (CSimon::GetInstance()->DirectionStair);
			CSimon::GetInstance()->vy = -SIMON_ONSTAIR_SPEED;
			CSimon::GetInstance()->isUP = true;
			CSimon::GetInstance()->SetCurrentAnimation(ONSTAIR_WALKING_UP_LEFT);
		}

	}
	else if (keyCode[DIK_UP])
	{
		if (CSimon::GetInstance()->DirectionStair == 1)
		{
			CSimon::GetInstance()->vx = SIMON_ONSTAIR_SPEED * (CSimon::GetInstance()->DirectionStair);
			CSimon::GetInstance()->vy = -SIMON_ONSTAIR_SPEED;
			CSimon::GetInstance()->SetCurrentAnimation(ONSTAIR_WALKING_UP_RIGHT);
			CSimon::GetInstance()->isUP = true;
		}
		else
		{
			CSimon::GetInstance()->vx = SIMON_ONSTAIR_SPEED * (CSimon::GetInstance()->DirectionStair);
			CSimon::GetInstance()->vy = -SIMON_ONSTAIR_SPEED;
			CSimon::GetInstance()->SetCurrentAnimation(ONSTAIR_WALKING_UP_LEFT);
			CSimon::GetInstance()->isUP = true;
		}
	}
	else if (keyCode[DIK_DOWN])
	{
		if (CSimon::GetInstance()->DirectionStair == 1)
		{
			CSimon::GetInstance()->vx = SIMON_ONSTAIR_SPEED * (-CSimon::GetInstance()->DirectionStair);
			CSimon::GetInstance()->vy = SIMON_ONSTAIR_SPEED;
			CSimon::GetInstance()->SetCurrentAnimation(ONSTAIR_WALKING_DOWN_LEFT);
			CSimon::GetInstance()->isUP = false;
		
		}
		else
		{
			CSimon::GetInstance()->vx = SIMON_ONSTAIR_SPEED * (-CSimon::GetInstance()->DirectionStair);
			CSimon::GetInstance()->vy = SIMON_ONSTAIR_SPEED;
			CSimon::GetInstance()->SetCurrentAnimation(ONSTAIR_WALKING_DOWN_RIGHT);
			CSimon::GetInstance()->isUP = false;
			
		}
	}
	else
	{
			if (CSimon::GetInstance()->getCurrentAnimation()->IsLastFrame())
			{
				if (CSimon::GetInstance()->DirectionStair == 1)
				{
					if (CSimon::GetInstance()->vx > 0)
					{

						CSimon::GetInstance()->ChangeState(new CSimonStateStanding(ONSTAIR_STANDING_UP_RIGHT));
						CSimon::GetInstance()->isUP = true;

					}
					else if (CSimon::GetInstance()->vx < 0)
					{
						CSimon::GetInstance()->ChangeState(new CSimonStateStanding(ONSTAIR_STANDING_DOWN_LEFT));
						CSimon::GetInstance()->isUP = false;
					}

				}
				else
				{
					if (CSimon::GetInstance()->vx > 0)
					{
						CSimon::GetInstance()->ChangeState(new CSimonStateStanding(ONSTAIR_STANDING_DOWN_RIGHT));
						CSimon::GetInstance()->isUP = false;
					
					}
					else if (CSimon::GetInstance()->vx < 0)
					{
						CSimon::GetInstance()->ChangeState(new CSimonStateStanding(ONSTAIR_STANDING_UP_LEFT));
						CSimon::GetInstance()->isUP = true;
					}

				}
			}

		
		
	}
};

void CSimonStateWalkingOnStair::Exit() {
	CSimon::GetInstance()->getCurrentAnimation()->SetIsLastFrame(false);
};
void CSimonStateWalkingOnStair::Enter()
{
	
};