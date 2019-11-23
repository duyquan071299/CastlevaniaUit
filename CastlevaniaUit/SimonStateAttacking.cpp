#include"SimonStateAttacking.h"
#include"SimonStateFalling.h"

void CSimonStateAttacking::Update(DWORD dt)
{
	if (CSimon::GetInstance()->whip != nullptr )
	{
		CSimon::GetInstance()->isHitting = true;

		if (CSimon::GetInstance()->isOnStair == true)
		{
			if (CSimon::GetInstance()->DirectionStair==1)
			{
				
				if (CSimon::GetInstance()->isUP)
				{
					CSimon::GetInstance()->whip->ChangeWeaponState(1);
					CSimon::GetInstance()->whip->nx = 1;
					CSimon::GetInstance()->whip->x = CSimon::GetInstance()->x - 23.4f;
					CSimon::GetInstance()->whip->y = CSimon::GetInstance()->y;
				}
				else
				{
					CSimon::GetInstance()->whip->ChangeWeaponState(-1);
					CSimon::GetInstance()->whip->nx = -1;
					CSimon::GetInstance()->whip->x = CSimon::GetInstance()->x - 76.4f;
					CSimon::GetInstance()->whip->y = CSimon::GetInstance()->y;
				}
			
			}
			else
			{
				
			
				if (CSimon::GetInstance()->isUP)
				{
					CSimon::GetInstance()->whip->ChangeWeaponState(-1);
					CSimon::GetInstance()->whip->nx = -1;
					CSimon::GetInstance()->whip->x = CSimon::GetInstance()->x - 76.4f;
					CSimon::GetInstance()->whip->y = CSimon::GetInstance()->y;
				}
				else
				{
					CSimon::GetInstance()->whip->ChangeWeaponState(1);
					CSimon::GetInstance()->whip->nx = 1;
					CSimon::GetInstance()->whip->x = CSimon::GetInstance()->x - 23.4f;
					CSimon::GetInstance()->whip->y = CSimon::GetInstance()->y;
				}

			}

			

		}
		else
		{

			if (CSimon::GetInstance()->nx >= 0)
			{
				CSimon::GetInstance()->whip->ChangeWeaponState(CSimon::GetInstance()->nx);
				CSimon::GetInstance()->whip->nx = 1;
				if (CSimon::GetInstance()->IsSitting == true)
				{
					CSimon::GetInstance()->whip->x = CSimon::GetInstance()->x - 23.4f;
					CSimon::GetInstance()->whip->y = CSimon::GetInstance()->y + 13.6f;
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
			
		}

	

	}

	if (CSimon::GetInstance()->getCurrentAnimation()->IsLastFrame() == true)
	{

		if (CSimon::GetInstance()->isOnStair)
		{
			if (CSimon::GetInstance()->DirectionStair==1)
			{
				if (CSimon::GetInstance()->isUP)
					CSimon::GetInstance()->ChangeState(new CSimonStateStanding(ONSTAIR_STANDING_UP_RIGHT));
				else
					CSimon::GetInstance()->ChangeState(new CSimonStateStanding(ONSTAIR_STANDING_DOWN_LEFT));
			}
			else
			{
				if (CSimon::GetInstance()->isUP)
					CSimon::GetInstance()->ChangeState(new CSimonStateStanding(ONSTAIR_STANDING_UP_LEFT));
				else
					CSimon::GetInstance()->ChangeState(new CSimonStateStanding(ONSTAIR_STANDING_DOWN_RIGHT));
			}
		}
		else
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

		CSimon::GetInstance()->isHitting = false;
		CSimon::GetInstance()->isThrowing = false;
	}

	//this->HandleKeyboard(keyCode);
}
void CSimonStateAttacking::HandleKeyboard(unordered_map<int, bool> keyCode)
{
	if (keyCode[DIK_UP] && CSimon::GetInstance()->isHitting==false&& CSimon::GetInstance()->count==1)
	{
		if (CSimon::GetInstance()->SecondWeapon != nullptr &&CSimon::GetInstance()->isThrowing==false && CSimon::GetInstance()->SecondWeapon->IsDead==true)
		{
			CSimon::GetInstance()->isThrowing = true;
			CSimon::GetInstance()->SecondWeapon->IsDead = false;
			CSimon::GetInstance()->whip = nullptr;
			int x = CSimon::GetInstance()->x+8;
			int y = CSimon::GetInstance()->y;
			CSimon::GetInstance()->SecondWeapon->SetPosition(x,y);
			CDagger * Dagger= dynamic_cast<CDagger *>(CSimon::GetInstance()->SecondWeapon);
			if (CSimon::GetInstance()->isOnStair)
			{
				if (CSimon::GetInstance()->DirectionStair)
				{
					if (CSimon::GetInstance()->isUP)
					{
						Dagger->ChangeAnimation(20);
						Dagger->nx = 1;
					}
					else
					{
						Dagger->ChangeAnimation(19);
						Dagger->nx = -1;
					}

				}
				else
				{


					if (CSimon::GetInstance()->isUP)
					{
						Dagger->ChangeAnimation(19);
						Dagger->nx = -1;
					}
					else
					{
						Dagger->ChangeAnimation(20);
						Dagger->nx = 1;
					}
				}
			}
			else
			{
				if (CSimon::GetInstance()->nx > 0)
				{
					Dagger->ChangeAnimation(20);
					Dagger->nx = 1;
				}
				else
				{
					Dagger->ChangeAnimation(19);
					Dagger->nx = -1;
				}

			}
			
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
	if (!CSimon::GetInstance()->IsOnAir)
	{
		CSimon::GetInstance()->vx = 0;
		if(CSimon::GetInstance()->isOnStair)
			CSimon::GetInstance()->vy = 0;

	}
		

	CSimon::GetInstance()->IsAttacking = true;

}