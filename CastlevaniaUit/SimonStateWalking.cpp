#include"SimonStateWalking.h"


void CSimonStateWalking::Update(DWORD dt) {};
void CSimonStateWalking::HandleKeyboard(unordered_map<int, bool> keyCode)
{

	if (keyCode[DIK_RIGHT])
	{
		CSimon::GetInstance()->SetCurrentAnimation(WALKING_RIGHT);
		CSimon::GetInstance()->vx = SIMON_RUNNING_SPEED;
//CSimon::GetInstance()->SetStateName(WALKING_RIGHT);
	}
	else if (keyCode[DIK_LEFT])
	{
		//CSimon::GetInstance()->SetStateName(WALKING_LEFT);
		CSimon::GetInstance()->SetCurrentAnimation(WALKING_LEFT);
		CSimon::GetInstance()->vx = -SIMON_RUNNING_SPEED;
	
	}
	else
	{
		if(CSimon::GetInstance()->vx >0)
			CSimon::GetInstance()->ChangeState(new CSimonStateStanding(STANDING_RIGHT));
		else
			CSimon::GetInstance()->ChangeState(new CSimonStateStanding(STANDING_LEFT));
		CSimon::GetInstance()->vx = 0;
	}
};

void CSimonStateWalking::Exit() {};
void CSimonStateWalking::Enter() {};