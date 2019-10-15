#include"SimonStateFalling.h"

void CSimonStateFalling::Update(DWORD dt)
{


	//this->HandleKeyboard(keyCode);
}
void CSimonStateFalling::HandleKeyboard(unordered_map<int, bool> keyCode)
{
	//CSimon::GetInstance()->vy = -SIMON_JUMPING_SPEED;
	if (CSimon::GetInstance()->vy==0)
	{
		CSimon::GetInstance()->vx = 0;
		if (CSimon::GetInstance()->nx >= 0)
			CSimon::GetInstance()->ChangeState(new CSimonStateStanding(STANDING_RIGHT));
		else
			CSimon::GetInstance()->ChangeState(new CSimonStateStanding(STANDING_LEFT));
	}

}

void CSimonStateFalling::Exit()
{
	CSimon::GetInstance()->IsFalling = false;
	CSimon::GetInstance()->IsJumping = false;
	CSimon::GetInstance()->IsOnAir = false;
}
void CSimonStateFalling::Enter()
{
	CSimon::GetInstance()->IsFalling = true;



}