#include"BossStage.h"
#include"StageManager.h"
#include"BatBoss.h"
void CBossStage::Loadresources()
{
	SetMapBound(MAP_BOUND_LEFT_STAGE_03, MAP_BOUND_RIGHT_STAGE_03);
	AllowRespawnGhost = true;
	GhostCount = 0;
	
}
void CBossStage::Render()
{

}

void CBossStage::DoorRender()
{

}
void CBossStage::Update(DWORD dt, CGrid * CurrentGrid)
{

	CCamera::GetInstance()->SetPosition(CSimon::GetInstance()->x - SCREEN_WIDTH / 2 + 40, 0);
	CCamera::GetInstance()->Update(MapBoundLeft, MapBoundRight);
		
	//Create Ghost mechanism
	if (AllowRespawnGhost && !CSimon::GetInstance()->isUsingStopWatch)
	{
		DWORD Now = GetTickCount();
		if (Now - TimeBetWeenGhostRespawn >= GHOST_RESPAWN_TIME)
		{
			if (CSimon::GetInstance()->x >= GHOST_RESPAWN_REGION_3_LEFT && CSimon::GetInstance()->x <= GHOST_RESPAWN_REGION_3_RIGHT)
			{
				if (GhostCount < 3)
				{
					if (CCamera::GetInstance()->x == MapBoundLeft)
					{
						CurrentGrid->AddObject(new CGhost(CCamera::GetInstance()->x + SCREEN_WIDTH - 30, GHOST_RESPAWN_POSITION_Y, -1));
						GhostCount++;
					}
					else if (CCamera::GetInstance()->x == (float)MapBoundRight - CCamera::GetInstance()->GetWidth() + 16)
					{
						CurrentGrid->AddObject(new CGhost(CCamera::GetInstance()->x + 30, GHOST_RESPAWN_POSITION_Y, 1));
						GhostCount++;
					}
					else if (CSimon::GetInstance()->vx > 0)
					{
						CurrentGrid->AddObject(new CGhost(CCamera::GetInstance()->x + 30, GHOST_RESPAWN_POSITION_Y, 1));
						GhostCount++;
					}
					else if (CSimon::GetInstance()->vx < 0)
					{
						CurrentGrid->AddObject(new CGhost(CCamera::GetInstance()->x + SCREEN_WIDTH - 30, GHOST_RESPAWN_POSITION_Y, -1));
						GhostCount++;
					}
					else if (CSimon::GetInstance()->vx == 0)
					{
						CurrentGrid->AddObject(new CGhost(CCamera::GetInstance()->x + SCREEN_WIDTH - 30, GHOST_RESPAWN_POSITION_Y, -1));
						GhostCount++;
					}


					if (GhostCount == 3)
					{
						AllowRespawnGhost = false;
					}
					TimeBetWeenGhostRespawn = GetTickCount();

				}
			}
		}
	}
	
	vector<LPGAMEOBJECT> listEnemy = CurrentGrid->GetListEnemies();


	for (int i = 0; i < listEnemy.size(); i++)
	{


		if (listEnemy[i]->IsDead == true || !listEnemy[i]->isIncamera)
		{
			if (dynamic_cast<CGhost *>(listEnemy[i]))
			{
				GhostCount--;
				CurrentGrid->RemoveAll(listEnemy[i]);
				if (GhostCount == 0)
				{
					TimeBetWeenGhostRespawn = GetTickCount();
					AllowRespawnGhost = true;
				}
				continue;
			}

		}


		if (dynamic_cast<CBatBoss *>(listEnemy[i]))
		{
			CScoreBoard::GetInstance()->SetBossHeal(dynamic_cast<CBatBoss *>(listEnemy[i])->GetHeal());
			if (CSimon::GetInstance()->isActiveBoss==true)
			{
				CSimon::GetInstance()->isActiveBoss = false;
				dynamic_cast<CBatBoss *>(listEnemy[i])->StartMoving();
				MapBoundLeft = 5121.0f;
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
				if (dynamic_cast<CGhost*>(listEnemy[i]))
					CSimon::GetInstance()->Score += 100;
				else if (dynamic_cast<CPanther*>(listEnemy[i]))
					CSimon::GetInstance()->Score += 200;
				dynamic_cast<CEnemy*>(listEnemy[i])->ChangeAnimation();
			}
			dynamic_cast<CEnemy *>(listEnemy[i])->ChangeAnimation();

		}
	}

}

