#include"SimonStateJumping.h"
#include"SimonStateFalling.h"
void CSimonStateJumping::Update(DWORD dt)
{
	

	//this->HandleKeyboard(keyCode);
}
void CSimonStateJumping::HandleKeyboard(unordered_map<int, bool> keyCode)
{
	if (CSimon::GetInstance()->vy > 0)
	{
		CSimon::GetInstance()->IsFalling = true;
		if(CSimon::GetInstance()->nx>=0)
			CSimon::GetInstance()->ChangeState(new CSimonStateFalling(SITTING_RIGHT));
		else
			CSimon::GetInstance()->ChangeState(new CSimonStateFalling(SITTING_LEFT));
	}
	
}

void CSimonStateJumping::Exit()
{

}
void CSimonStateJumping::Enter()
{
	CSimon::GetInstance()->IsOnAir = true;

}