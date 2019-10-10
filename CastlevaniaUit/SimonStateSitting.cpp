#include"SimonStateSitting.h"


void CSimonStateSitting::Update(DWORD dt) {};
void CSimonStateSitting::HandleKeyboard(unordered_map<int, bool> keyCode)
{
	if (!keyCode[DIK_DOWN] || keyCode[DIK_UP])
	{
		
		if (CSimon::GetInstance()->nx > 0)
			CSimon::GetInstance()->ChangeState(new CSimonStateStanding(STANDING_RIGHT));
		else
			CSimon::GetInstance()->ChangeState(new CSimonStateStanding(STANDING_LEFT));
		
		
		

	}
	

};

void CSimonStateSitting::Exit() {
	CSimon::GetInstance()->IsSitting = false;
};
void CSimonStateSitting::Enter() 
{
	CSimon::GetInstance()->vx = 0;
	CSimon::GetInstance()->IsSitting = true;
	CSimon::GetInstance()->IsOnAir = false;
};