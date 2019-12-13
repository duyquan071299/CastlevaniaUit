#include"BatStage.h"
#include"SimonStateWalking.h"
#include"StageManager.h"
#include"UnderGroundStage.h"
#include"BossStage.h"
void CBatStage::Loadresources()
{
	Door = new CDoor(DOOR_POS_X_2, DOOR_POS_y_2);
	SetMapBound(MAP_BOUND_LEFT_STAGE_02, MAP_BOUND_RIGHT_STAGE_02);
	AllowRespawnBat = true;
	TimeBetWeenBatRespawn = GetTickCount();
}
void CBatStage::Render()
{

}

void CBatStage::DoorRender()
{
	Door->Render();
}
void CBatStage::Update(DWORD dt, CGrid * CurrentGrid)
{

	Door->Update(dt);
	if (CCamera::GetInstance()->isWithSimon)
	{
		CCamera::GetInstance()->SetPosition(CSimon::GetInstance()->x - SCREEN_WIDTH / 2 + 40, 0);
		CCamera::GetInstance()->Update(MapBoundLeft, MapBoundRight);

	}
	else
	{
		if (CCamera::GetInstance()->x + SCREEN_WIDTH / 2 < CSimon::GetInstance()->x)
			CCamera::GetInstance()->SetPosition((int)CCamera::GetInstance()->x + 0.2 *dt, 0);
		else  if (CSimon::GetInstance()->IsFreeze && Door->x > CSimon::GetInstance()->x && Door->GetCurrentState() != OPEN)
		{
			Door->ChangeState(OPENNING);
		}
		else if (Door->GetCurrentState() == OPEN)
		{
			MapBoundRight = MAP_BOUND_RIGHT_STAGE_03;
			if (CSimon::GetInstance()->x > Door->x)
			{
				Door->ChangeState(CLOSING);
			}
			else
			{
				CSimon::GetInstance()->IsFreeze = false;
				CSimon::GetInstance()->IsOnAnimation = true;
				CSimon::GetInstance()->ChangeState(new CSimonStateWalking(WALKING_RIGHT));
			}


		}
		else if (Door->GetCurrentState() == CLOSE)
		{
			if ((int)CCamera::GetInstance()->x >= Door->x + 16)
			{
				CSimon::GetInstance()->IsFreeze = false;
				CCamera::GetInstance()->isWithSimon = true;
				CStageManager::GetInstance()->LoadStage(new CBossStage());
			}
			else
			{
				CCamera::GetInstance()->SetPosition((int)CCamera::GetInstance()->x + 0.1 *dt, 0);
			}

		}

	}
	//Create Bat mechanism
	if (AllowRespawnBat && !CSimon::GetInstance()->isUsingStopWatch)
	{
			
		DWORD Now = GetTickCount();
		if (Now - TimeBetWeenBatRespawn >= BAT_RESPAWN_TIME)
		{
			if (CSimon::GetInstance()->x >= BAT_RESPAWN_REGION_LEFT && CSimon::GetInstance()->x <= BAT_RESPAWN_REGION_RIGHT && CSimon::GetInstance()->y < SCREEN_HEIGHT - 100)
			{
				if (BatCount < 1)
				{
					if (CCamera::GetInstance()->x == MapBoundLeft)
					{
						CurrentGrid->AddObject(new CBat(CCamera::GetInstance()->x + SCREEN_WIDTH - 20, CSimon::GetInstance()->y + 16, -1));
					}
					else if (CSimon::GetInstance()->nx > 0)
					{
						CurrentGrid->AddObject(new CBat(CCamera::GetInstance()->x + SCREEN_WIDTH - 20, CSimon::GetInstance()->y + 16, -1));
					}
					else if (CSimon::GetInstance()->nx < 0)
					{
						CurrentGrid->AddObject(new CBat(CCamera::GetInstance()->x + 20, CSimon::GetInstance()->y + 16, 1));
					}
					BatCount++;
					if (BatCount == 1)
					{
						AllowRespawnBat = false;
					}
				}
			}
		}
	}

	vector<LPGAMEOBJECT> listEnemy = CurrentGrid->GetListEnemies();

	for (int i = 0; i < listEnemy.size(); i++)
	{
		if (listEnemy[i]->IsDead == true || !listEnemy[i]->isIncamera)
		{
			if (dynamic_cast<CBat *>(listEnemy[i]))
			{
				BatCount--;
				CurrentGrid->RemoveAll(listEnemy[i]);
				TimeBetWeenBatRespawn = GetTickCount();
				AllowRespawnBat = true;
				continue;

			}
		}
		
		if (CSimon::GetInstance()->isUsingStopWatch)
		{
			dynamic_cast<CEnemy *>(listEnemy[i])->isFrozen = true;
		}
		else
		{
			dynamic_cast<CEnemy *>(listEnemy[i])->isFrozen = false;
		}
		if (CSimon::GetInstance()->isUsingCross)
		{
			if (!dynamic_cast<CEnemy *>(listEnemy[i])->isBurning)
			{
				if (dynamic_cast<CBat*>(listEnemy[i]))
				{
					CSimon::GetInstance()->Score += 200;
					dynamic_cast<CEnemy *>(listEnemy[i])->ChangeAnimation();
				}
			}
			

		}
	}
	if (CSimon::GetInstance()->isUnderGround == true)
	{
		CStageManager::GetInstance()->LoadStage(new CUnderGroundStage());
	}
}

