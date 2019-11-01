#include"SimonStateWalking.h"
#include"SimonStateSitting.h"

void CSimonStateWalking::Update(DWORD dt) {};
void CSimonStateWalking::HandleKeyboard(unordered_map<int, bool> keyCode)
{
	if (keyCode[DIK_DOWN])
	{
		if (CSimon::GetInstance()->nx > 0)
			CSimon::GetInstance()->ChangeState(new CSimonStateSitting(SITTING_RIGHT));
		else
			CSimon::GetInstance()->ChangeState(new CSimonStateSitting(SITTING_LEFT));

	}
	else if (keyCode[DIK_RIGHT])
	{
		CSimon::GetInstance()->nx = 1;
		if (keyCode[DIK_LEFT])
		{
			if(CSimon::GetInstance()->nx>0)
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
		if (CSimon::GetInstance()->vx > 0)
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