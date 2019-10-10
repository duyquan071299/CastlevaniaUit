#include"SimonStateAttacking.h"

void CSimonStateAttacking::Update(DWORD dt)
{


	//this->HandleKeyboard(keyCode);
}
void CSimonStateAttacking::HandleKeyboard(unordered_map<int, bool> keyCode)
{
	if (CSimon::GetInstance()->getCurrentAnimation()->IsLastFrame() == true)
	{
		
		if (CSimon::GetInstance()->nx >= 0)
			CSimon::GetInstance()->ChangeState(new CSimonStateStanding(STANDING_RIGHT));
		else
			CSimon::GetInstance()->ChangeState(new CSimonStateStanding(STANDING_LEFT));
	}
	

}

void CSimonStateAttacking::Exit()
{
	CSimon::GetInstance()->IsAttacking = false;
	CSimon::GetInstance()->getCurrentAnimation()->SetIsLastFrame(false);
}
void CSimonStateAttacking::Enter()
{
	if(CSimon::GetInstance()->IsOnAir==false)
		CSimon::GetInstance()->vx = 0;
	CSimon::GetInstance()->IsAttacking = true;

}