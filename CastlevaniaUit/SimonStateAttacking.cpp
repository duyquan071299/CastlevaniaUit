#include"SimonStateAttacking.h"

void CSimonStateAttacking::Update(DWORD dt)
{


	//this->HandleKeyboard(keyCode);
}
void CSimonStateAttacking::HandleKeyboard(unordered_map<int, bool> keyCode)
{
	//CSimon::GetInstance()->vy = -SIMON_JUMPING_SPEED;
	//CSimon::GetInstance()->vx = 0;
	if (CSimon::GetInstance()->getCurrentAnimation()->IsLastFrame() == true)
	{
		CSimon::GetInstance()->IsAttacking = false;
		CSimon::GetInstance()->getCurrentAnimation()->SetIsLastFrame(false);
		//CSimon::GetInstance()->getCurrentAnimation()
		if (CSimon::GetInstance()->nx >= 0)
			CSimon::GetInstance()->ChangeState(new CSimonStateStanding(STANDING_RIGHT));
		else
			CSimon::GetInstance()->ChangeState(new CSimonStateStanding(STANDING_LEFT));
	}
	



}

void CSimonStateAttacking::Exit()
{

}
void CSimonStateAttacking::Enter()
{
	CSimon::GetInstance()->vx = 0;
	CSimon::GetInstance()->vy = 0;
	CSimon::GetInstance()->SetStateName(STANDING);

}