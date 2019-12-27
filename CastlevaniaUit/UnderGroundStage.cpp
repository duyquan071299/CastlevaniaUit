#include"UnderGroundStage.h"
#include"StageManager.h"
#include"BatStage.h"

void CUnderGroundStage::Loadresources()
{
	TimeBetWeenKappaRespawn = GetTickCount();
	this->CurrentStageType = UNDERGROUND_STAGE;
	FirstRespawn = true;
	TimeLimit = 3000;
	SetMapBound(UNDER_GROUND_BOUND_LEFT, UNDER_GROUND_BOUND_RIGHT);
	CScoreBoard::GetInstance()->SetStage("02");
	AllowRespawnKappa = true;
	KappaCount = 0;
}
void CUnderGroundStage::Render()
{

}
void CUnderGroundStage::Update(DWORD dt, CGrid * CurrentGrid )
{

	CCamera::GetInstance()->SetPosition(CSimon::GetInstance()->x - SCREEN_WIDTH / 2 + 40, SCREEN_WIDTH - 40);
	CCamera::GetInstance()->Update(MapBoundLeft, MapBoundRight);
	//Create Kappa mechanism
	if (AllowRespawnKappa && KappaCount < 2&& !CSimon::GetInstance()->isUsingStopWatch)
	{
		DWORD Now = GetTickCount();
		if (Now - TimeBetWeenKappaRespawn >= TimeLimit)
		{
			if (CSimon::GetInstance()->x >= KAPPA_RESPAWN_REGION_1_LEFT && CSimon::GetInstance()->x <= KAPPA_RESPAWN_REGION_1_RIGHT && CSimon::GetInstance()->y >= SCREEN_HEIGHT)
			{

				if (FirstRespawn)
				{
					FirstRespawn = false;
					TimeLimit = 2000;

					if (CSimon::GetInstance()->x >= KAPPA_RESPAWN_ZONE_1 && CSimon::GetInstance()->x <= KAPPA_RESPAWN_ZONE_2)
					{

						CurrentGrid->AddObject(new CKappa(KAPPA_RESPAWN_X_2, KAPPA_RESPAWN_Y, CSimon::GetInstance()->x > KAPPA_RESPAWN_X_2 ? 1 : -1));
						CurrentGrid->AddObject(new CKappa(KAPPA_RESPAWN_X_3, KAPPA_RESPAWN_Y, CSimon::GetInstance()->x > KAPPA_RESPAWN_X_1 ? 1 : -1));
						KappaCount = 2;

					}
					else if (CSimon::GetInstance()->x >= KAPPA_RESPAWN_ZONE_2 && CSimon::GetInstance()->x <= KAPPA_RESPAWN_ZONE_3)
					{
						CurrentGrid->AddObject(new CKappa(KAPPA_RESPAWN_X_1, KAPPA_RESPAWN_Y, CSimon::GetInstance()->x > KAPPA_RESPAWN_X_1 ? 1 : -1));
						CurrentGrid->AddObject(new CKappa(KAPPA_RESPAWN_X_3, KAPPA_RESPAWN_Y, CSimon::GetInstance()->x > KAPPA_RESPAWN_X_3 ? 1 : -1));
						KappaCount = 2;

					}
					else if (CSimon::GetInstance()->x >= KAPPA_RESPAWN_ZONE_3 && CSimon::GetInstance()->x <= KAPPA_RESPAWN_ZONE_4)
					{
						CurrentGrid->AddObject(new CKappa(KAPPA_RESPAWN_X_1, KAPPA_RESPAWN_Y, CSimon::GetInstance()->x > KAPPA_RESPAWN_X_1 ? 1 : -1));
						CurrentGrid->AddObject(new CKappa(KAPPA_RESPAWN_X_2, KAPPA_RESPAWN_Y, CSimon::GetInstance()->x > KAPPA_RESPAWN_X_2 ? 1 : -1));
						KappaCount = 2;

					}
					else
					{

						CurrentGrid->AddObject(new CKappa(KAPPA_RESPAWN_X_6, KAPPA_RESPAWN_Y, CSimon::GetInstance()->x > KAPPA_RESPAWN_X_1 ? 1 : -1));
						CurrentGrid->AddObject(new CKappa(KAPPA_RESPAWN_X_7, KAPPA_RESPAWN_Y, CSimon::GetInstance()->x > KAPPA_RESPAWN_X_2 ? 1 : -1));
						KappaCount = 2;
					}

				}
				else if (KappaCount < 2)
				{
					int random;
					if (CSimon::GetInstance()->x >= KAPPA_RESPAWN_ZONE_1 && CSimon::GetInstance()->x <= KAPPA_RESPAWN_ZONE_2)
					{
						random = rand() % 3;
						if (random == 0)
							random = KAPPA_RESPAWN_X_2;
						else if (random == 1)
							random = KAPPA_RESPAWN_X_3;
						else
							random = KAPPA_RESPAWN_X_4;
						CurrentGrid->AddObject(new CKappa(random, KAPPA_RESPAWN_Y, CSimon::GetInstance()->x > random ? 1 : -1));
						KappaCount++;
					}
					else if (CSimon::GetInstance()->x >= KAPPA_RESPAWN_ZONE_2 && CSimon::GetInstance()->x <= KAPPA_RESPAWN_ZONE_3)
					{
						random = rand() % 3;
						if (random == 0)
							random = KAPPA_RESPAWN_X_1;
						else if (random == 1)
							random = KAPPA_RESPAWN_X_3;
						else
							random = KAPPA_RESPAWN_X_4;
						CurrentGrid->AddObject(new CKappa(random, KAPPA_RESPAWN_Y, CSimon::GetInstance()->x > random ? 1 : -1));
						KappaCount++;
					}
					else if (CSimon::GetInstance()->x >= KAPPA_RESPAWN_ZONE_3 && CSimon::GetInstance()->x <= KAPPA_RESPAWN_ZONE_4)
					{
						random = rand() % 3;
						if (random == 0)
							random = KAPPA_RESPAWN_X_2;
						else if (random == 1)
							random = KAPPA_RESPAWN_X_4;
						else
							random = KAPPA_RESPAWN_X_5;
						CurrentGrid->AddObject(new CKappa(random, KAPPA_RESPAWN_Y, CSimon::GetInstance()->x > random ? 1 : -1));
						KappaCount++;
					}
					else if (CSimon::GetInstance()->x >= KAPPA_RESPAWN_ZONE_4 && CSimon::GetInstance()->x <= KAPPA_RESPAWN_ZONE_5)
					{
						random = rand() % 3;
						if (random == 0)
							random = KAPPA_RESPAWN_X_2;
						else if (random == 1)
							random = KAPPA_RESPAWN_X_3;
						else
							random = KAPPA_RESPAWN_X_5;
						CurrentGrid->AddObject(new CKappa(random, KAPPA_RESPAWN_Y, CSimon::GetInstance()->x > random ? 1 : -1));
						KappaCount++;
					}
					else if (CSimon::GetInstance()->x >= KAPPA_RESPAWN_ZONE_5 && CSimon::GetInstance()->x <= KAPPA_RESPAWN_ZONE_6)
					{
						random = rand() % 3;
						if (random == 0)
							random = KAPPA_RESPAWN_X_3;
						else if (random == 1)
							random = KAPPA_RESPAWN_X_4;
						else
							random = KAPPA_RESPAWN_X_6;
						CurrentGrid->AddObject(new CKappa(random, KAPPA_RESPAWN_Y, CSimon::GetInstance()->x > random ? 1 : -1));
						KappaCount++;
					}
					else if (CSimon::GetInstance()->x >= KAPPA_RESPAWN_ZONE_6 && CSimon::GetInstance()->x <= KAPPA_RESPAWN_ZONE_7)
					{
						random = rand() % 3;
						if (random == 0)
							random = KAPPA_RESPAWN_X_4;
						else if (random == 1)
							random = KAPPA_RESPAWN_X_5;
						else
							random = KAPPA_RESPAWN_X_7;
						CurrentGrid->AddObject(new CKappa(random, KAPPA_RESPAWN_Y, CSimon::GetInstance()->x > random ? 1 : -1));
						KappaCount++;
					}
					else if (CSimon::GetInstance()->x >= KAPPA_RESPAWN_ZONE_7 && CSimon::GetInstance()->x <= KAPPA_RESPAWN_ZONE_8)
					{
						random = rand() % 2;
						if (random == 0)
							random = KAPPA_RESPAWN_X_5;
						else if (random == 1)
							random = KAPPA_RESPAWN_X_6;
						CurrentGrid->AddObject(new CKappa(random, KAPPA_RESPAWN_Y, CSimon::GetInstance()->x > random ? 1 : -1));
						KappaCount++;
					}
					else
					{
						random = rand() % 3;
						if (random == 0)
							random = KAPPA_RESPAWN_X_5;
						else if (random == 1)
							random = KAPPA_RESPAWN_X_6;
						else
							random = KAPPA_RESPAWN_X_7;
						CurrentGrid->AddObject(new CKappa(random, KAPPA_RESPAWN_Y, CSimon::GetInstance()->x > random ? 1 : -1));
						KappaCount++;
					}

				}


				TimeBetWeenKappaRespawn = GetTickCount();

			}
		}

	}

	vector<LPGAMEOBJECT> listEnemy = CurrentGrid->GetListEnemies();

	for (int i = 0; i < listEnemy.size(); i++)
	{

		if (dynamic_cast<CKappa *>(listEnemy[i]))
		{

			if (listEnemy[i]->IsDead == true || !listEnemy[i]->isIncamera)
			{
				if (listEnemy[i]->IsDead == true && listEnemy[i]->y >= KAPPA_RESPAWN_Y)
					CEffectDatabase::GetInstance()->AddBubbleEffect(listEnemy[i]->x, listEnemy[i]->y);
				CurrentGrid->RemoveAll(listEnemy[i]);
				KappaCount--;
				continue;
			}

			if (dynamic_cast<CKappa *>(listEnemy[i])->isAtacking && dynamic_cast<CKappa *>(listEnemy[i])->isFire == false)
			{
				dynamic_cast<CKappa *>(listEnemy[i])->isFire = true;
				CurrentGrid->AddObject(new CEnemyBullet(listEnemy[i]->x, listEnemy[i]->y + 5, listEnemy[i]->nx));
			}
			if (dynamic_cast<CKappa *>(listEnemy[i])->y == KAPPA_RESPAWN_Y)
				CEffectDatabase::GetInstance()->AddBubbleEffect(listEnemy[i]->x, listEnemy[i]->y);



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

	if (CSimon::GetInstance()->isUnderGround == false)
	{
		CStageManager::GetInstance()->LoadStage(new CBatStage());
	}

}