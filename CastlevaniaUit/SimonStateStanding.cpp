#include"SimonStateStanding.h"
void CSimonStateStanding::Update(DWORD dt)
{
	//this->HandleKeyboard(keyCode);
}
void CSimonStateStanding::HandleKeyboard(unordered_map<int, bool> keyCode)
{
	if (keyCode[DIK_RIGHT])
	{
		CSimon::GetInstance()->ChangeState(new CSimonStateWalking(WALKING_RIGHT));

	}
	else if(keyCode[DIK_LEFT])
	{
		CSimon::GetInstance()->ChangeState(new CSimonStateWalking(WALKING_LEFT));
	}
	else if (keyCode[DIK_DOWN])
	{
		//CSimon::GetInstance()->ChangeState(new CSimonStateWalking());
	}
}

void CSimonStateStanding::Exit()
{

}
void CSimonStateStanding::Enter()
{
	CSimon::GetInstance()->vx = 0;
	CSimon::GetInstance()->vy = 0;
	CSimon::GetInstance()->SetStateName(STANDING);

}