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
		CSimon::GetInstance()->vx = 0;
		CSimon::GetInstance()->IsStanding = true;
		CSimon::GetInstance()->IsSitting = false;

	}
	

};

void CSimonStateSitting::Exit() {};
void CSimonStateSitting::Enter() {};