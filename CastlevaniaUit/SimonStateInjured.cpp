#include"SimonStateInjured.h"

void CSimonStateInjured::Update(DWORD dt)
{



}
void CSimonStateInjured::HandleKeyboard(unordered_map<int, bool> keyCode)
{
	

}

void CSimonStateInjured::Exit()
{
	

}
void CSimonStateInjured::Enter()
{
	CSimon::GetInstance()->StartUntouchable();
}