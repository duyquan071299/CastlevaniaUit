#include"IndoorStage.h"
#include"BatStage.h"
#include"SimonStateWalking.h"
#include"StageManager.h"
void CIndoorStage::Loadresources()
{
	Door = new CDoor(DOOR_POS_X_1, DOOR_POS_y_1);
	SetMapBound(MAP_BOUND_LEFT_STAGE_01, MAP_BOUND_RIGHT_STAGE_01);
	AllowRespawnGhost = true;
	GhostCount = 0;
	PantherCount = 3;
	CScoreBoard::GetInstance()->SetStage("01");
	PantherAtX1 = PantherAtX2 = PantherAtX3 = 1;
	this->CurrentStageType = INDOOR_STAGE;
}
void CIndoorStage::Render()
{
	
}

void CIndoorStage::DoorRender()
{
	Door->Render();
}
void CIndoorStage::Update(DWORD dt, CGrid * CurrentGrid)
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
			MapBoundRight = MAP_BOUND_RIGHT_STAGE_02;
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
				CStageManager::GetInstance()->LoadStage(new CBatStage());
				CCamera::GetInstance()->isWithSimon = true;
			}
			else
			{
				CCamera::GetInstance()->SetPosition((int)CCamera::GetInstance()->x + 0.1 *dt, 0);
			}

		}
	}

	DWORD Now = GetTickCount();
	//Create Ghost mechanism
	if (AllowRespawnGhost&&!CSimon::GetInstance()->isUsingStopWatch)
	{
		if (Now - TimeBetWeenGhostRespawn >= GHOST_RESPAWN_TIME)
		{
			if ((CSimon::GetInstance()->x >= GHOST_RESPAWN_REGION_1_LEFT && CSimon::GetInstance()->x <= GHOST_RESPAWN_REGION_1_RIGHT) || (CSimon::GetInstance()->x >= GHOST_RESPAWN_REGION_2_LEFT && CSimon::GetInstance()->x <= GHOST_RESPAWN_REGION_2_RIGHT))
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

	//Create Panther mechanism
	if (PantherCount < 3)
	{

		if (CSimon::GetInstance()->x >= PANTHER_RESPAWN_ZONE_X_RIGHT_1)
		{
			if (PantherAtX1 == 0)
			{
				CurrentGrid->AddObject(new CPanther(PANTHER_RESPAWN_X_1, PANTHER_RESPAWN_Y_1, 1));
				PantherAtX1 = 1;
				PantherCount++;
			}

		}
		if (CSimon::GetInstance()->x >= PANTHER_RESPAWN_ZONE_X_RIGHT_2)
		{
			if (PantherAtX2 == 0)
			{
				CurrentGrid->AddObject(new CPanther(PANTHER_RESPAWN_X_2, PANTHER_RESPAWN_Y_2, 1));
				PantherAtX2 = 1;
				PantherCount++;
			}

		}
		if (CSimon::GetInstance()->x >= PANTHER_RESPAWN_ZONE_X_RIGHT_3)
		{
			if (PantherAtX3 == 0)
			{
				CurrentGrid->AddObject(new CPanther(PANTHER_RESPAWN_X_3, PANTHER_RESPAWN_Y_1, 1));
				PantherAtX3 = 1;
				PantherCount++;
			}


		}
		if (CSimon::GetInstance()->x <= PANTHER_RESPAWN_ZONE_X_LEFT_1)
		{
			if (PantherAtX1 == 0)
			{
				CurrentGrid->AddObject(new CPanther(PANTHER_RESPAWN_X_1, PANTHER_RESPAWN_Y_1, -1));
				PantherAtX1 = 1;
				PantherCount++;
			}

		}
		if (CSimon::GetInstance()->x <= PANTHER_RESPAWN_ZONE_X_LEFT_2)
		{
			if (PantherAtX2 == 0)
			{
				CurrentGrid->AddObject(new CPanther(PANTHER_RESPAWN_X_2, PANTHER_RESPAWN_Y_2, -1));
				PantherAtX2 = 1;
				PantherCount++;
			}

		}
		if (CSimon::GetInstance()->x <= PANTHER_RESPAWN_ZONE_X_LEFT_3)
		{
			if (PantherAtX3 == 0)
			{
				CurrentGrid->AddObject(new CPanther(PANTHER_RESPAWN_X_3, PANTHER_RESPAWN_Y_1, -1));
				PantherAtX3 = 1;
				PantherCount++;
			}

		}




	}

	vector<LPGAMEOBJECT> listEnemy = CurrentGrid->GetListEnemies();

	
	for (int i = 0; i < listEnemy.size(); i++)
	{
		if (!CCamera::GetInstance()->isWithSimon)
		{
			GhostCount--;
			CurrentGrid->RemoveAll(listEnemy[i]);
		}
		else
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
				else if (dynamic_cast<CPanther*>(listEnemy[i]))
				{
					CurrentGrid->RemoveAll(listEnemy[i]);
					PantherCount--;
					continue;
				}
			}
			else if (dynamic_cast<CPanther *>(listEnemy[i]) && dynamic_cast<CPanther *>(listEnemy[i])->isSitting)
			{
				if (CSimon::GetInstance()->x > PANTHER_RUNNING_X_LEFT_1 && CSimon::GetInstance()->x < PANTHER_RUNNING_X_RIGHT_1 && listEnemy[i]->x> PANTHER_RUNNING_X_LEFT_1 &&  listEnemy[i]->x < PANTHER_RUNNING_X_RIGHT_1)
				{
					dynamic_cast<CPanther *>(listEnemy[i])->isRunning = true;
					dynamic_cast<CPanther *>(listEnemy[i])->isSitting = false;
					dynamic_cast<CPanther *>(listEnemy[i])->ChangeAni();
					PantherAtX1 = 0;

				}
				else if (CSimon::GetInstance()->x > PANTHER_RUNNING_X_LEFT_2 && CSimon::GetInstance()->x < PANTHER_RUNNING_X_RIGHT_2 && listEnemy[i]->x> PANTHER_RUNNING_X_LEFT_2 &&  listEnemy[i]->x < PANTHER_RUNNING_X_RIGHT_2)
				{
					dynamic_cast<CPanther *>(listEnemy[i])->isRunning = true;
					dynamic_cast<CPanther *>(listEnemy[i])->isSitting = false;
					dynamic_cast<CPanther *>(listEnemy[i])->ChangeAni();
					PantherAtX2 = 0;

				}
				else if (CSimon::GetInstance()->x > PANTHER_RUNNING_X_LEFT_3 && CSimon::GetInstance()->x < PANTHER_RUNNING_X_RIGHT_3 && listEnemy[i]->x> PANTHER_RUNNING_X_LEFT_3 &&  listEnemy[i]->x < PANTHER_RUNNING_X_RIGHT_3)
				{
					dynamic_cast<CPanther *>(listEnemy[i])->isRunning = true;
					dynamic_cast<CPanther *>(listEnemy[i])->isSitting = false;
					dynamic_cast<CPanther *>(listEnemy[i])->ChangeAni();
					PantherAtX3 = 0;
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
						CSimon::GetInstance()->Score += KILL_GHOST_SCORE;
					else if (dynamic_cast<CPanther*>(listEnemy[i]))
						CSimon::GetInstance()->Score += KILL_PANTHER_SCORE;
					dynamic_cast<CEnemy*>(listEnemy[i])->ChangeAnimation();
				}
				dynamic_cast<CEnemy *>(listEnemy[i])->ChangeAnimation();

			}

		}



	}


	


}

