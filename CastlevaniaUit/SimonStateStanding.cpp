#include"SimonStateStanding.h"
#include"SimonStateSitting.h"
void CSimonStateStanding::Update(DWORD dt)
{
	//this->HandleKeyboard(keyCode);
}
void CSimonStateStanding::HandleKeyboard(unordered_map<int, bool> keyCode)
{
	if (keyCode[DIK_RIGHT]&& !keyCode[DIK_LEFT])
	{
		CSimon::GetInstance()->ChangeState(new CSimonStateWalking(WALKING_RIGHT));
		CSimon::GetInstance()->nx = 1;
		CSimon::GetInstance()->IsStanding = false;
		CSimon::GetInstance()->IsMoving = true;
	}
	else if(keyCode[DIK_LEFT]&& !keyCode[DIK_RIGHT])
	{
		CSimon::GetInstance()->ChangeState(new CSimonStateWalking(WALKING_LEFT));
		CSimon::GetInstance()->nx = -1;
		CSimon::GetInstance()->IsStanding = false;
		CSimon::GetInstance()->IsMoving = true;

	}
	else if (keyCode[DIK_DOWN]&& !keyCode[DIK_UP])
	{

		if (CSimon::GetInstance()->nx> 0)
			CSimon::GetInstance()->ChangeState(new CSimonStateSitting(SITTING_RIGHT));
		else
			CSimon::GetInstance()->ChangeState(new CSimonStateSitting(SITTING_LEFT));
		CSimon::GetInstance()->vx = 0;
		CSimon::GetInstance()->IsStanding = false;
		CSimon::GetInstance()->IsSitting = true;
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