#include"PlayScene.h"
#include"SimonStateWalking.h"


void CPlayScene::Loadresources(int level) {
	CCamera::GetInstance()->SetWH(SCREEN_WIDTH, 400);
	CCamera::GetInstance()->SetPosition(SCREEN_WIDTH / 2,
		0 );

	
	Simon = CSimon::GetInstance();

	switch (level)
	{
	case 0:
	{
		Simon->Respawn();
		CurrentMap = new CMap("Resources\\Maps\\Scene1.txt", "Resources\\Maps\\Scene_1.png");
		MapBoundRight= CurrentMap->GetMapWidth();
		MapBoundLeft = 0;
		Simon->x = 0;
		this->Level = level;
		Simon->AtLevel = level;
		Grid = new CGrid(CurrentMap->GetMapWidth(), CurrentMap->GetMapHeight(), "Resources\\Maps\\Scene1_Object.txt");
		ScoreBoard = new CScoreBoard(0.0f, 0.0f);
		break;
	}
	case 1:
	{
		Simon->Respawn();
		CCamera::GetInstance()->isWithSimon = true;
		CurrentMap = new CMap("Resources\\Maps\\Scene2.txt", "Resources\\Maps\\Scene_2.png");
		Door = new CDoor(3056, 112);
		Simon->x =3200;
		Simon->y = RESPAWN_POSITION_Y;
		Simon->y = 500;
		this->Level = level;
		Simon->AtLevel = level;
		Simon->isInCastle = true;
		MapBoundLeft = 0;
		MapBoundRight = 3072;
		//MapBoundRight = 5000;
		TimeBetWeenGhostRespawn = GetTickCount();
		Grid = new CGrid(CurrentMap->GetMapWidth(), CurrentMap->GetMapHeight(), "Resources\\Maps\\Scene2_Object.txt");
		AllowRespawnGhost = true;
	}
	}
	

};

void CPlayScene::OnKeyDown(int KeyCode)
{
	if (!Simon->IsFreeze && !Simon->IsOnAnimation &&!Simon->CollectItem)
	{
		keys[KeyCode] = true;
		Simon->OnKeyDown(KeyCode);
		if (KeyCode == DIK_A)
		{
			delete CurrentMap;
			Loadresources(1);
			TimeLimit = 3000;
			


		}
		else if (KeyCode == DIK_B)
		{
			Panther->isRunning = true;
			Panther->isSitting = false;
			Panther->ChangeAni();
		}

	}

	
	
}
void  CPlayScene::OnKeyUp(int KeyCode)
{
	keys[KeyCode] = false;
	Simon->OnKeyUp(KeyCode);
}

void CPlayScene::Render()
{
	
	CurrentMap->Draw();
	ScoreBoard->Render();
	
	
	if (CCamera::GetInstance()->isWithSimon  )
	{
		auto list = Grid->GetListMapObject();
		for (int i = 0; i < list.size(); i++)
		{
			list.at(i)->Render();
		}

	}
	
	if (Door != nullptr)
		Door->Render();

	Simon->Render();
	if ((Simon->IsOnAnimation||Simon->IsRespawn)&&Simon->vx>0&&!this->Level)
	{
		LPSPRITE TileSet = new CSprite(MAP, 0, 1);
		TileSet->Settexture(CTextureDatabase::GetInstance()->GetTexture(HIDING_OBJECT));
		TileSet->SetFrameWH(96, 128);
		TileSet->Draw((float)1408, (float)240, default_color);
	}
	

}

void CPlayScene::Update(DWORD dt)
{

	
	vector<LPGAMEOBJECT> Objects = Grid->GetListMapObject();
	for (int i = 0; i < Objects.size(); i++)
	{
		Objects.at(i)->Update(dt, &Grid->GetListObjectCanContactWithMapObject(Objects.at(i)));
		Grid->MoveObject(Objects.at(i), Objects.at(i)->PrevX, Objects.at(i)->PrevY);
	}

	//Walking through door mechanism
	if (Simon->isInCastle==true)
	{
		
		if (CCamera::GetInstance()->isWithSimon)
		{
			if (Simon->y < SCREEN_HEIGHT - 36)
			{
				CScoreBoard::GetInstance()->y = 0;
				CCamera::GetInstance()->SetPosition(Simon->x - SCREEN_WIDTH / 2 + 40, 0);
				CCamera::GetInstance()->Update(MapBoundLeft, MapBoundRight);
			}
			else
			{
				CScoreBoard::GetInstance()->y = SCREEN_HEIGHT;
				CCamera::GetInstance()->SetPosition(Simon->x - SCREEN_WIDTH / 2 + 40, SCREEN_HEIGHT);
	
				CCamera::GetInstance()->Update(UnderGroundMapBoundLeft, UnderGroundMapBoundRight);
			}


		}
		else
		{
	
			if (CCamera::GetInstance()->x + SCREEN_WIDTH / 2 < Simon->x)
				CCamera::GetInstance()->SetPosition((int)CCamera::GetInstance()->x + 0.1 *dt, 0);
			else  if (Simon->IsFreeze && Door->x > Simon->x && Door->GetCurrentState() != OPEN)
			{
				Door->ChangeState(OPENNING);
			}
			else if (Door->GetCurrentState() == OPEN)
			{
				MapBoundRight = 4096;
				if (Simon->x > Door->x)
				{
					Door->ChangeState(CLOSING);
				}
				else
				{
					Simon->IsFreeze = false;
					Simon->IsOnAnimation = true;
					Simon->ChangeState(new CSimonStateWalking(WALKING_RIGHT));
				}


			}
			else if (Door->GetCurrentState() == CLOSE)
			{
				if ((int)CCamera::GetInstance()->x >= Door->x + 16)
				{
					Simon->IsFreeze = false;
					MapBoundLeft = Door->x + 16;
				
					CCamera::GetInstance()->isWithSimon = true;
					AllowRespawnBat = true;
					TimeBetWeenBatRespawn = GetTickCount();
				}
				else
				{
					CCamera::GetInstance()->SetPosition((int)CCamera::GetInstance()->x + 0.1 *dt, 0);
				}

			}


		}

	}
	else
	{
		CCamera::GetInstance()->SetPosition(Simon->x - SCREEN_WIDTH / 2 + 40, 0);
		CCamera::GetInstance()->Update(MapBoundLeft, MapBoundRight);
	}
	ScoreBoard->Update();
	if (Simon->isUsingStopWatch &&FrozenTime==0)
	{
		FrozenTime = GetTickCount();
	}

	if (Simon->isUsingCross && CrossTime == 0)
	{
		CrossTime = GetTickCount();
	}
	DWORD Now = GetTickCount();
	if (Now - FrozenTime >= FROZEN_TIME)
	{
		Simon->isUsingStopWatch = false;
		FrozenTime = 0;
	}
	
	if (Now - CrossTime >= CROSS_TIME)
	{
		Simon->isUsingCross = false;
		CrossTime = 0;
	}

	//Create Enemy mechanism
	if (Simon->isInCastle)
	{
		DWORD Now = GetTickCount();
		//Create Ghost mechanism
		if (AllowRespawnGhost)
		{
			if (Now - TimeBetWeenGhostRespawn >= GHOST_RESPAWN_TIME)
			{
				if ((Simon->x >= GHOST_RESPAWN_REGION_1_LEFT && Simon->x <= GHOST_RESPAWN_REGION_1_RIGHT)||(Simon->x >= GHOST_RESPAWN_REGION_2_LEFT && Simon->x <= GHOST_RESPAWN_REGION_2_RIGHT))
				{
					if (GhostCount < 3)
					{
						if (CCamera::GetInstance()->x == MapBoundLeft)
						{
							Grid->AddObject(new CGhost(CCamera::GetInstance()->x + SCREEN_WIDTH - 30, RESPAWN_POSITION_Y, -1));
							GhostCount++;
						}
						else if (CCamera::GetInstance()->x  == (float)MapBoundRight - CCamera::GetInstance()->GetWidth() + 16)
						{
							Grid->AddObject(new CGhost(CCamera::GetInstance()->x +  30, RESPAWN_POSITION_Y, 1));
							GhostCount++;
						}
						else if (Simon->vx > 0)
						{
							Grid->AddObject(new CGhost(CCamera::GetInstance()->x + 30, RESPAWN_POSITION_Y, 1));
							GhostCount++;
						}
						else if (Simon->vx < 0)
						{
							Grid->AddObject(new CGhost(CCamera::GetInstance()->x + SCREEN_WIDTH -30, RESPAWN_POSITION_Y, -1));
							GhostCount++;
						}
						else if (Simon->vx == 0)
						{
							Grid->AddObject(new CGhost(CCamera::GetInstance()->x + SCREEN_WIDTH -30, RESPAWN_POSITION_Y, -1));
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
		//Create Bat mechanism
		if (AllowRespawnBat)
		{
			if (Now - TimeBetWeenBatRespawn >= BAT_RESPAWN_TIME)
			{
				if (Simon->x >= BAT_RESPAWN_REGION_LEFT && Simon->x <= BAT_RESPAWN_REGION_RIGHT && Simon->y < SCREEN_HEIGHT - 100)
				{
					if (BatCount < 1)
					{
						if (CCamera::GetInstance()->x == MapBoundLeft)
						{
							Grid->AddObject(new CBat(CCamera::GetInstance()->x + SCREEN_WIDTH - 20, Simon->y+16, -1));
						}
						else if (Simon->nx > 0)
						{
							Grid->AddObject(new CBat(CCamera::GetInstance()->x + SCREEN_WIDTH - 20, Simon->y+16, -1));
						}
						else if (Simon->nx < 0)
						{
							Grid->AddObject(new CBat(CCamera::GetInstance()->x + 20, Simon->y+16, 1));
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
		//Create Kappa mechanism
		if (AllowRespawnKappa && KappaCount<2)
		{
			if (Now - TimeBetWeenKappaRespawn >= TimeLimit)
			{
				if (Simon->x >= KAPPA_RESPAWN_REGION_1_LEFT && Simon->x <= KAPPA_RESPAWN_REGION_1_RIGHT && Simon->y >= SCREEN_HEIGHT)
				{

					if (FirstRespawn)
					{
						FirstRespawn = false;
						TimeLimit = 2000;

						if (Simon->x >= KAPPA_RESPAWN_X_1 - 90 && Simon->x <= KAPPA_RESPAWN_X_1 + 64)
						{
						
							Grid->AddObject(new CKappa(KAPPA_RESPAWN_X_2, KAPPA_RESPAWN_Y, Simon->x > KAPPA_RESPAWN_X_2 ? 1 : -1));
							Grid->AddObject(new CKappa(KAPPA_RESPAWN_X_3, KAPPA_RESPAWN_Y, Simon->x > KAPPA_RESPAWN_X_1 ? 1 : -1));
							KappaCount = 2;
							
						}
						else if (Simon->x >= KAPPA_RESPAWN_X_2 - 64 && Simon->x <= KAPPA_RESPAWN_X_2 + 51)
						{
							Grid->AddObject(new CKappa(KAPPA_RESPAWN_X_1, KAPPA_RESPAWN_Y, Simon->x > KAPPA_RESPAWN_X_1 ? 1 : -1));
							Grid->AddObject(new CKappa(KAPPA_RESPAWN_X_3, KAPPA_RESPAWN_Y, Simon->x > KAPPA_RESPAWN_X_3 ? 1 : -1));
							KappaCount = 2;
							
						}
						else if (Simon->x >= KAPPA_RESPAWN_X_3 - 51 && Simon->x <= KAPPA_RESPAWN_X_3 + 75)
						{
							Grid->AddObject(new CKappa(KAPPA_RESPAWN_X_1, KAPPA_RESPAWN_Y, Simon->x > KAPPA_RESPAWN_X_1 ? 1 : -1));
							Grid->AddObject(new CKappa(KAPPA_RESPAWN_X_2, KAPPA_RESPAWN_Y, Simon->x > KAPPA_RESPAWN_X_2 ? 1 : -1));
							KappaCount = 2;
							
						}
						
					}
					else if (KappaCount < 2)
					{
						int random;
						if (Simon->x >= KAPPA_RESPAWN_ZONE_1 && Simon->x <= KAPPA_RESPAWN_ZONE_2)
						{
							random = rand() % 3;
							if (random == 0)
								random = KAPPA_RESPAWN_X_2;
							else if (random == 1)
								random = KAPPA_RESPAWN_X_3;
							else
								random = KAPPA_RESPAWN_X_4;
							Grid->AddObject(new CKappa(random, KAPPA_RESPAWN_Y, Simon->x > random ? 1 : -1));
							KappaCount++;
						}
						else if (Simon->x >= KAPPA_RESPAWN_ZONE_1 && Simon->x <= KAPPA_RESPAWN_ZONE_3)
						{
							random = rand() % 3;
							if (random == 0)
								random = KAPPA_RESPAWN_X_1;
							else if (random == 1)
								random = KAPPA_RESPAWN_X_3;
							else
								random = KAPPA_RESPAWN_X_4;
							Grid->AddObject(new CKappa(random, KAPPA_RESPAWN_Y, Simon->x > random ? 1 : -1));
							KappaCount++;
						}
						else if (Simon->x >= KAPPA_RESPAWN_ZONE_3 && Simon->x <= KAPPA_RESPAWN_ZONE_4)
						{
							random = rand() % 3;
							if (random == 0)
								random = KAPPA_RESPAWN_X_2;
							else if (random == 1)
								random = KAPPA_RESPAWN_X_4;
							else
								random = KAPPA_RESPAWN_X_5;
							Grid->AddObject(new CKappa(random, KAPPA_RESPAWN_Y, Simon->x > random ? 1 : -1));
							KappaCount++;
						}
						else if (Simon->x >= KAPPA_RESPAWN_ZONE_4 && Simon->x <= KAPPA_RESPAWN_ZONE_5)
						{
							random = rand() % 3;
							if (random == 0)
								random = KAPPA_RESPAWN_X_2;
							else if (random == 1)
								random = KAPPA_RESPAWN_X_3;
							else
								random = KAPPA_RESPAWN_X_5;
							Grid->AddObject(new CKappa(random, KAPPA_RESPAWN_Y, Simon->x > random ? 1 : -1));
							KappaCount++;
						}
						else if (Simon->x >= KAPPA_RESPAWN_ZONE_5 && Simon->x <= KAPPA_RESPAWN_ZONE_6)
						{
							random = rand() % 3;
							if (random == 0)
								random = KAPPA_RESPAWN_X_3;
							else if (random == 1)
								random = KAPPA_RESPAWN_X_4;
							else
								random = KAPPA_RESPAWN_X_6;
							Grid->AddObject(new CKappa(random, KAPPA_RESPAWN_Y, Simon->x > random ? 1 : -1));
							KappaCount++;
						}
						else if (Simon->x >= KAPPA_RESPAWN_ZONE_6 && Simon->x <= KAPPA_RESPAWN_ZONE_7)
						{
							random = rand() % 3;
							if (random == 0)
								random = KAPPA_RESPAWN_X_4;
							else if (random == 1)
								random = KAPPA_RESPAWN_X_5;
							else
								random = KAPPA_RESPAWN_X_7;
							Grid->AddObject(new CKappa(random, KAPPA_RESPAWN_Y, Simon->x > random ? 1 : -1));
							KappaCount++;
						}
						else if (Simon->x >= KAPPA_RESPAWN_ZONE_7 && Simon->x <= KAPPA_RESPAWN_ZONE_8)
						{
							random = rand() % 2;
							if (random == 0)
								random = KAPPA_RESPAWN_X_5;
							else if (random == 1)
								random = KAPPA_RESPAWN_X_6;
							Grid->AddObject(new CKappa(random, KAPPA_RESPAWN_Y, Simon->x > random ? 1 : -1));
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
							Grid->AddObject(new CKappa(random, KAPPA_RESPAWN_Y, Simon->x > random ? 1 : -1));
							KappaCount++;
						}

					}


						TimeBetWeenKappaRespawn = GetTickCount();
					
				}
			}

		}
		//Create Panther mechanism
		if (PantherCount<3)
		{
			
				if (Simon->x >= PANTHER_RESPAWN_ZONE_X_RIGHT_1)
				{
					if (PantherAtX1 == 0)
					{
						Grid->AddObject(new CPanther(PANTHER_RESPAWN_X_1, PANTHER_RESPAWN_Y_1, 1));
						PantherAtX1 = 1;
						PantherCount++;
					}
					
				}
				if (Simon->x >= PANTHER_RESPAWN_ZONE_X_RIGHT_2)
				{
					if (PantherAtX2 == 0)
					{
						Grid->AddObject(new CPanther(PANTHER_RESPAWN_X_2, PANTHER_RESPAWN_Y_2, 1));
						PantherAtX2 = 1;
						PantherCount++;
					}
					
				}
				if (Simon->x >= PANTHER_RESPAWN_ZONE_X_RIGHT_3)
				{
					if (PantherAtX3 == 0)
					{
						Grid->AddObject(new CPanther(PANTHER_RESPAWN_X_3, PANTHER_RESPAWN_Y_1, 1));
						PantherAtX3 = 1;
						PantherCount++;
					}
				

				}
				if (Simon->x <= PANTHER_RESPAWN_ZONE_X_LEFT_1)
				{
					if (PantherAtX1 == 0)
					{
						Grid->AddObject(new CPanther(PANTHER_RESPAWN_X_1, PANTHER_RESPAWN_Y_1, -1));
						PantherAtX1 = 1;
						PantherCount++;
					}
					
				}
				if (Simon->x <= PANTHER_RESPAWN_ZONE_X_LEFT_2)
				{
					if (PantherAtX2 == 0)
					{
						Grid->AddObject(new CPanther(PANTHER_RESPAWN_X_2, PANTHER_RESPAWN_Y_2, -1));
						PantherAtX2 = 1;
						PantherCount++;
					}
				
				}
				if (Simon->x <= PANTHER_RESPAWN_ZONE_X_LEFT_3)
				{
					if (PantherAtX3 == 0)
					{
						Grid->AddObject(new CPanther(PANTHER_RESPAWN_X_3, PANTHER_RESPAWN_Y_1, -1));
						PantherAtX3 = 1;
						PantherCount++;
					}
					
				}

		
				

		}
	}

	

	vector<LPGAMEOBJECT> listEnemy = Grid->GetListEnemies();

	UpdateSimon();
	for (int i = 0; i < listEnemy.size(); i++)
	{
		if (!CCamera::GetInstance()->isWithSimon)
		{
			GhostCount--;
			Grid->RemoveAll(listEnemy[i]);
		}
		else
		{
			if (listEnemy[i]->IsDead == true || !listEnemy[i]->isIncamera)
			{
				if (dynamic_cast<CGhost *>(listEnemy[i]))
				{
					GhostCount--;
					Grid->RemoveAll(listEnemy[i]);
					if (GhostCount == 0)
					{
						TimeBetWeenGhostRespawn = GetTickCount();
						AllowRespawnGhost = true;
					}
					continue;
				}
				else if (dynamic_cast<CBat *>(listEnemy[i]))
				{
					BatCount--;
					Grid->RemoveAll(listEnemy[i]);
					TimeBetWeenBatRespawn = GetTickCount();
					AllowRespawnBat = true;
					continue;
			
				}
				else if (dynamic_cast<CKappa*>(listEnemy[i]))
				{
					Grid->RemoveAll(listEnemy[i]);
					KappaCount--;
					continue;
					
				}
				else if (dynamic_cast<CPanther*>(listEnemy[i]))
				{
					Grid->RemoveAll(listEnemy[i]);
					PantherCount--;
					continue;
				}
			}

			if (dynamic_cast<CKappa *>(listEnemy[i]))
			{

				if (dynamic_cast<CKappa *>(listEnemy[i])->isAtacking && dynamic_cast<CKappa *>(listEnemy[i])->isFire == false)
				{
					dynamic_cast<CKappa *>(listEnemy[i])->isFire = true;
					Grid->AddObject(new CEnemyBullet(listEnemy[i]->x, listEnemy[i]->y + 5, listEnemy[i]->nx));
				}

			}
			else if (dynamic_cast<CPanther *>(listEnemy[i])&& dynamic_cast<CPanther *>(listEnemy[i])->isSitting)
			{
				if (Simon->x > PANTHER_RUNNING_X_LEFT_1 && Simon->x < PANTHER_RUNNING_X_RIGHT_1 && listEnemy[i]->x> PANTHER_RUNNING_X_LEFT_1 &&  listEnemy[i]->x < PANTHER_RUNNING_X_RIGHT_1)
				{
					dynamic_cast<CPanther *>(listEnemy[i])->isRunning = true;
					dynamic_cast<CPanther *>(listEnemy[i])->isSitting = false;
					dynamic_cast<CPanther *>(listEnemy[i])->ChangeAni();
					PantherAtX1 = 0;

				}
				else if (Simon->x > PANTHER_RUNNING_X_LEFT_2 && Simon->x < PANTHER_RUNNING_X_RIGHT_2 && listEnemy[i]->x> PANTHER_RUNNING_X_LEFT_2 &&  listEnemy[i]->x < PANTHER_RUNNING_X_RIGHT_2)
				{
					dynamic_cast<CPanther *>(listEnemy[i])->isRunning = true;
					dynamic_cast<CPanther *>(listEnemy[i])->isSitting = false;
					dynamic_cast<CPanther *>(listEnemy[i])->ChangeAni();
					PantherAtX2 = 0;

				}
				else if (Simon->x > PANTHER_RUNNING_X_LEFT_3 && Simon->x < PANTHER_RUNNING_X_RIGHT_3 && listEnemy[i]->x> PANTHER_RUNNING_X_LEFT_3 &&  listEnemy[i]->x < PANTHER_RUNNING_X_RIGHT_3)
				{
					dynamic_cast<CPanther *>(listEnemy[i])->isRunning = true;
					dynamic_cast<CPanther *>(listEnemy[i])->isSitting = false;
					dynamic_cast<CPanther *>(listEnemy[i])->ChangeAni();
					PantherAtX3 = 0;
				}

			}

			if (Simon->isUsingStopWatch)
			{
				dynamic_cast<CEnemy *>(listEnemy[i])->isFrozen = true;
			}
			else
			{
				dynamic_cast<CEnemy *>(listEnemy[i])->isFrozen = false;
			}
			if (Simon->isUsingCross)
			{
				dynamic_cast<CEnemy *>(listEnemy[i])->ChangeAnimation();
			}
		
		}
		


	}






	if (!Simon->IsFreeze)
	{
		if(!Simon->IsOnAnimation)
			Simon->HandleKeyboard(keys);
		Simon->Update(dt, &(Grid->GetListObjectCanContactWith(Simon)));
		if (Simon->whip != nullptr)
			Simon->whip->Update(dt, &(Grid->GetListObjectCanContactWith(Simon->whip)));
	}
	if (Door != nullptr)
		Door->Update(dt, &(Grid->GetListObjectCanContactWith(Door)));
	CurrentMap->Update(dt);
	
	
}




void CPlayScene::UpdateSimon()
{
	if (Simon->IsRespawn)
	{
		Simon->IsRespawn = false;
		delete CurrentMap;
		Loadresources(1);
		return;
	}

	if (keys[DIK_Z] == true)
		Simon->count++;
	else
		Simon->count = 0;

	if (Simon->y < SCREEN_HEIGHT - 36)
	{
		
		if (Simon->vx < 0 && Simon->x < MapBoundLeft - 9)
			Simon->x = MapBoundLeft - 10;
		else if(Simon->vx>=0 && Simon->x > MapBoundRight -48)
			Simon->x = MapBoundRight - 48;
		SetUpTime = true;
		FirstRespawn = true;
		KappaCount = 0;
	
	}
	else
	{
		
		if (SetUpTime)
		{
			AllowRespawnKappa = true;
			TimeBetWeenKappaRespawn = GetTickCount();
			FirstRespawn = true;
			SetUpTime = false;
			TimeLimit = 3000;
		}
		if (Simon->vx < 0 && Simon->x < UnderGroundMapBoundLeft - 9)
			Simon->x = UnderGroundMapBoundLeft - 10;
		else if (Simon->vx >= 0 && Simon->x > UnderGroundMapBoundRight - 64)
			Simon->x = UnderGroundMapBoundRight - 64;
	}

	
	

	if (Simon->isThrowing && Simon->WeaponType!=WATCH)
	{
		Simon->AllowThrow = true;
		Simon->isThrowing = false;
		auto listObject = Grid->GetListMapObject();
		for (int i = 0; i < listObject.size(); i++)
		{
			if (dynamic_cast<CWeapon *>(listObject[i]))
				Simon->AllowThrow = false;
			

		}
		if (Simon->AllowThrow)
		{
			Grid->AddObject(Simon->CreateSecondWeapond());

		}
	}


}

