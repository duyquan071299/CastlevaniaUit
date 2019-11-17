#include"SimonStateWalking.h"
#include"SimonStateSitting.h"

void CSimonStateWalking::Update(DWORD dt) 
{
	if (CSimon::GetInstance()->IsOnAnimation)
	{
		if (abs(CSimon::GetInstance()->x - CSimon::GetInstance()->CheckPoint) >= 1.5)
		{
			if (CSimon::GetInstance()->x < CSimon::GetInstance()->CheckPoint)
			{
				CSimon::GetInstance()->SetCurrentAnimation(WALKING_RIGHT);
				if (CSimon::GetInstance()->AtLevel == 0)
					CSimon::GetInstance()->vx = 0.05;
				else
					CSimon::GetInstance()->vx = SIMON_RUNNING_SPEED;
			}
			else
			{
				CSimon::GetInstance()->SetCurrentAnimation(WALKING_LEFT);
				if (CSimon::GetInstance()->AtLevel == 0)
					CSimon::GetInstance()->vx = -0.05;
				else
					CSimon::GetInstance()->vx = -SIMON_RUNNING_SPEED;
			}



		}
		else
		{
			if (CSimon::GetInstance()->vx < 0)
				CSimon::GetInstance()->CheckPoint += 300;
			else
			{
				CSimon::GetInstance()->IsOnAnimation = false;
				CSimon::GetInstance()->IsFreeze = true;
				CSimon::GetInstance()->ChangeState(new CSimonStateStanding(STANDING_RIGHT));
			}
			
		
		}
		
		

	
	}
};
void CSimonStateWalking::HandleKeyboard(unordered_map<int, bool> keyCode)
{
	if (keyCode[DIK_DOWN])
	{
		if (CSimon::GetInstance()->vx > 0)
			CSimon::GetInstance()->ChangeState(new CSimonStateSitting(SITTING_RIGHT));
		else
			CSimon::GetInstance()->ChangeState(new CSimonStateSitting(SITTING_LEFT));

	}
	else if (keyCode[DIK_RIGHT])
	{
		CSimon::GetInstance()->nx = 1;
		if (keyCode[DIK_LEFT])
		{
			if(CSimon::GetInstance()->vx>0)
				CSimon::GetInstance()->ChangeState(new CSimonStateStanding(STANDING_RIGHT));
			else
				CSimon::GetInstance()->ChangeState(new CSimonStateStanding(STANDING_LEFT));
			return;
		}
			
		CSimon::GetInstance()->SetCurrentAnimation(WALKING_RIGHT);
		CSimon::GetInstance()->vx =SIMON_RUNNING_SPEED;
	}
	else if (keyCode[DIK_LEFT])
	{
		CSimon::GetInstance()->nx = -1;
		//CSimon::GetInstance()->SetStateName(WALKING_LEFT);
		CSimon::GetInstance()->SetCurrentAnimation(WALKING_LEFT);
		CSimon::GetInstance()->vx = -SIMON_RUNNING_SPEED;
	
	}
	else
	{
		if (CSimon::GetInstance()->nx >= 0)
			CSimon::GetInstance()->ChangeState(new CSimonStateStanding(STANDING_RIGHT));
		else
			CSimon::GetInstance()->ChangeState(new CSimonStateStanding(STANDING_LEFT));
	}
};

void CSimonStateWalking::Exit() {
	CSimon::GetInstance()->IsMoving = false;
};
void CSimonStateWalking::Enter() 
{
	CSimon::GetInstance()->IsMoving = true;
	CSimon::GetInstance()->IsOnAir = false;
};