#include"SimonDead.h"

void CSimonStateDead::Update(DWORD dt)
{

	if (CSimon::GetInstance()->getCurrentAnimation()->IsLastFrame() == true && CSimon::GetInstance()->IsLoading == false)
	{
		CSimon::GetInstance()->IsRespawn = true;
		CSimon::GetInstance()->IsLoading = true;
		CSimon::GetInstance()->getCurrentAnimation()->SetIsLastFrame(false);
	}


		

}
void CSimonStateDead::HandleKeyboard(unordered_map<int, bool> keyCode)
{


}

void CSimonStateDead::Exit()
{
	CSimon::GetInstance()->IsDead = false;
}
void CSimonStateDead::Enter()
{
	CSimon::GetInstance()->IsDead = true;
}