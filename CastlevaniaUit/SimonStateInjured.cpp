#include"SimonStateInjured.h"

void CSimonStateInjured::Update(DWORD dt)
{



}
void CSimonStateInjured::HandleKeyboard(unordered_map<int, bool> keyCode)
{
	

}

void CSimonStateInjured::Exit()
{
	
	CSimon::GetInstance()->isInjured = false;
}
void CSimonStateInjured::Enter()
{
	CSimon::GetInstance()->StartUntouchable();
	CSimon::GetInstance()->isInjured = true;
}