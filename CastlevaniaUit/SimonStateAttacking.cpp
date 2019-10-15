#include"SimonStateAttacking.h"
#include"SimonStateFalling.h"

void CSimonStateAttacking::Update(DWORD dt)
{
	if (CSimon::GetInstance()->nx >= 0)
	{
		CSimon::GetInstance()->whip->ChangeWeaponState(CSimon::GetInstance()->nx);
		CSimon::GetInstance()->whip->nx = 1;
		if (CSimon::GetInstance()->IsSitting == true)
		{
			
			CSimon::GetInstance()->whip->x = CSimon::GetInstance()->x - 23.4f;
			CSimon::GetInstance()->whip->y = CSimon::GetInstance()->y+13.6f;
		}
		else
		{
			CSimon::GetInstance()->whip->x = CSimon::GetInstance()->x - 23.4f;
			CSimon::GetInstance()->whip->y = CSimon::GetInstance()->y;
		}
	
	}
	else
	{
		CSimon::GetInstance()->whip->ChangeWeaponState(CSimon::GetInstance()->nx);
		CSimon::GetInstance()->whip->nx = -1;
		if (CSimon::GetInstance()->IsSitting == true)
		{
			CSimon::GetInstance()->whip->x = CSimon::GetInstance()->x - 76.4f;
			CSimon::GetInstance()->whip->y = CSimon::GetInstance()->y + 13.6f;
		}
		else
		{
			
			CSimon::GetInstance()->whip->x = CSimon::GetInstance()->x - 76.4f;
			CSimon::GetInstance()->whip->y = CSimon::GetInstance()->y;
		}
	
	}

	//this->HandleKeyboard(keyCode);
}
void CSimonStateAttacking::HandleKeyboard(unordered_map<int, bool> keyCode)
{
	if (CSimon::GetInstance()->getCurrentAnimation()->IsLastFrame() == true)
	{	
		
		if (CSimon::GetInstance()->nx > 0)
		{
			if (CSimon::GetInstance()->IsOnAir == true)
			{
				CSimon::GetInstance()->IsFalling = true;
				CSimon::GetInstance()->ChangeState(new CSimonStateFalling(STANDING_RIGHT));
			}
			else
				CSimon::GetInstance()->ChangeState(new CSimonStateStanding(STANDING_RIGHT));
				
		}
		else
		{
			if (CSimon::GetInstance()->IsOnAir == true)
			{
				CSimon::GetInstance()->IsFalling = true;
				CSimon::GetInstance()->ChangeState(new CSimonStateFalling(STANDING_LEFT));
			}
			CSimon::GetInstance()->ChangeState(new CSimonStateStanding(STANDING_LEFT));
		}
		}
			
	

}

void CSimonStateAttacking::Exit()
{
	CSimon::GetInstance()->IsAttacking = false;
	CSimon::GetInstance()->getCurrentAnimation()->SetIsLastFrame(false);
	CSimon::GetInstance()->whip = nullptr;
}
void CSimonStateAttacking::Enter()
{
	if(CSimon::GetInstance()->IsOnAir==false)
		CSimon::GetInstance()->vx = 0;
	CSimon::GetInstance()->IsAttacking = true;

}