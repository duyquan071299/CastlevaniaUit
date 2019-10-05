#include"SimonStateWalking.h"

void CSimonStateWalking::Update(DWORD dt) {};
void CSimonStateWalking::HandleKeyboard(unordered_map<int, bool> keyCode)
{
	if (keyCode[DIK_RIGHT])
	{
		//CSimon::GetInstance()->SetStateName(WALKING_RIGHT);
		SetState(WALKING_LEFT);
		CSimon::GetInstance()->vx = SIMON_RUNNING_SPEED;

	
	}
	else if (keyCode[DIK_LEFT])
	{
		//CSimon::GetInstance()->SetStateName(WALKING_LEFT);
		SetState(WALKING_LEFT);
		CSimon::GetInstance()->vx = -SIMON_RUNNING_SPEED;
	}
	else
	{
		CSimon::GetInstance()->ChangeState(new CSimonStateWalking(STANDING_RIGHT));

	}
};

void CSimonStateWalking::Exit() {};
void CSimonStateWalking::Enter() {};