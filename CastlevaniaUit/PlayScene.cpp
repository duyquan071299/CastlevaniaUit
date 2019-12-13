#include"PlayScene.h"
#include"SimonStateWalking.h"
#include"EffectDatabase.h"
#include"OutDoorStage.h"
#include"IndoorStage.h"
#include"UnderGroundStage.h"
#include"BatStage.h"
#include"BossStage.h"
void CPlayScene::Loadresources(int level) {
	CCamera::GetInstance()->SetWH(SCREEN_WIDTH, 400);
	CCamera::GetInstance()->SetPosition(SCREEN_WIDTH / 2,
		0 );

	
	Simon = CSimon::GetInstance();
	ScoreBoard = CScoreBoard::GetInstance();
	

	switch (level)
	{
	case 0:
	{
		Simon->Respawn();
		CurrentMap = new CMap("Resources\\Maps\\Scene1.txt", "Resources\\Maps\\Scene_1.png");
		Simon->x = 0;
		Simon->AtLevel = level;
		//Grid = new CGrid(CurrentMap->GetMapWidth(), CurrentMap->GetMapHeight(), "Resources\\Maps\\Scene1_Object.txt");
		Grid = new CGrid();
		Grid->AddObjectToGrid("Resources\\Maps\\Grid1.txt");
		CStageManager::GetInstance()->LoadStage(new COutDoorStage());
		ScoreBoard->SetUp(0.0f, 0.0f);
		break;
	}
	case 1:
	{
		delete Grid;
		Simon->Respawn();
		CCamera::GetInstance()->isWithSimon = true;
		CurrentMap = new CMap("Resources\\Maps\\Scene2.txt", "Resources\\Maps\\Scene_2.png");
		Simon->y = RESPAWN_POSITION_Y;
		Simon->AtLevel = level;
		Grid = new CGrid(CurrentMap->GetMapWidth(), CurrentMap->GetMapHeight(), "Resources\\Maps\\Scene2_Object.txt");
		//Grid = new CGrid();
		//Grid->AddObjectToGrid("Resources\\Maps\\Grid2.txt");
	}
	}
	

};

void CPlayScene::OnKeyDown(int KeyCode)
{
	if (!Simon->IsFreeze && !Simon->IsOnAnimation &&!Simon->CollectItem)
	{
		keys[KeyCode] = true;
		Simon->OnKeyDown(KeyCode);

		if (KeyCode == DIK_Q)
		{
			Simon->x = 0;
			Loadresources(1);
			CStageManager::GetInstance()->LoadStage(new CIndoorStage());
		}

		if (KeyCode == DIK_W)
		{
			Simon->x = 3200;
			CStageManager::GetInstance()->LoadStage(new CBatStage());
		}

		if (KeyCode == DIK_E)
		{
			Simon->x = 5140;
			CStageManager::GetInstance()->LoadStage(new CBossStage());
		}


		if (KeyCode == DIK_Y)
		{
			Simon->x = 3050;
		}

		if (KeyCode == DIK_1)
		{
			Simon->ChangeSecondWeapon(AXE);
			Simon->WeaponShot = 2;
			Simon->Heart = 99;
		}

		if (KeyCode == DIK_2)
		{
			Simon->ChangeSecondWeapon(DAGGER);
			Simon->WeaponShot = 2;
			Simon->Heart = 99;
		}

		if (KeyCode == DIK_3)
		{
			Simon->ChangeSecondWeapon(WATCH);
			Simon->WeaponShot = 2;
			Simon->Heart = 99;
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
	if (Simon->isWalkingInOutGround)
	{
		return;
	}
	CurrentMap->Draw();
	ScoreBoard->Render();
	if (CCamera::GetInstance()->isWithSimon)
	{
		auto list = Grid->GetListMapObject();
		for (int i = 0; i < list.size(); i++)
		{
			list.at(i)->Render();
		}

	}
	CStageManager::GetInstance()->GetCurrentStage()->DoorRender();
	Simon->Render();
	CStageManager::GetInstance()->GetCurrentStage()->Render();
	for(int i=0;i<CEffectDatabase::GetInstance()->GetListEffect().size();i++)
		CEffectDatabase::GetInstance()->GetListEffect()[i]->Render();

}

void CPlayScene::Update(DWORD dt)
{

	for (int i = 0; i < CEffectDatabase::GetInstance()->GetListEffect().size(); i++)
	{
		CEffectDatabase::GetInstance()->GetListEffect()[i]->Update(dt);
		if (CEffectDatabase::GetInstance()->GetListEffect()[i]->CheckIsDone())
		{
			CEffectDatabase::GetInstance()->RemoveForListEffect(i);
			i--;
		}
			


	}
	vector<LPGAMEOBJECT> Objects = Grid->GetListMapObject();
	for (int i = 0; i < Objects.size(); i++)
	{
		Objects.at(i)->Update(dt, &Grid->GetListObjectCanContactWithMapObject(Objects.at(i)));
		Grid->MoveObject(Objects.at(i), Objects.at(i)->PrevX, Objects.at(i)->PrevY);
	
	}

	CStageManager::GetInstance()->GetCurrentStage()->Update(dt, Grid);

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


	UpdateSimon();


	if (!Simon->IsFreeze)
	{
		if(!Simon->IsOnAnimation)
			Simon->HandleKeyboard(keys);
		Simon->Update(dt, &(Grid->GetListObjectCanContactWith(Simon)));
		if (Simon->whip != nullptr)
			Simon->whip->Update(dt, &(Grid->GetListObjectCanContactWith(Simon->whip)));
	}
	CurrentMap->Update(dt);
	
	
}




void CPlayScene::UpdateSimon()
{
	if (Simon->IsRespawn)
	{
		Simon->IsRespawn = false;
		delete CurrentMap;
		Loadresources(1);
		CStageManager::GetInstance()->LoadStage(new CIndoorStage());
		return;
	}


	

	if (keys[DIK_Z] == true)
		Simon->count++;
	else
		Simon->count = 0;


	if (Simon->vx < 0 && Simon->x < CStageManager::GetInstance()->GetCurrentStage()->GetMapBoundLeft() - 9)
		Simon->x = (float)(CStageManager::GetInstance()->GetCurrentStage()->GetMapBoundLeft() - 10);
	else if (Simon->vx >= 0 && Simon->x > CStageManager::GetInstance()->GetCurrentStage()->GetMapBoundRight() - 48)
		Simon->x = (float)(CStageManager::GetInstance()->GetCurrentStage()->GetMapBoundRight() - 48);

	

	if (Simon->isThrowing && Simon->WeaponType!=WATCH)
	{
		Simon->AllowThrow = true;
		Simon->isThrowing = false;
		auto listObject = Grid->GetListMapObject();
		int WeaponCount=0;
		for (int i = 0; i < listObject.size(); i++)
		{
			if (dynamic_cast<CWeapon *>(listObject[i]))
				WeaponCount++;
			if(Simon->WeaponShot== WeaponCount)
				Simon->AllowThrow = false;
			

		}
		if (Simon->AllowThrow)
		{
			if (Simon->WeaponType == DAGGER || Simon->WeaponType == HOLYWATER||Simon->WeaponType==AXE)
			{
				if (Simon->Heart < 1)
					return;
				else
					Simon->Heart -= 1;

			}
			Grid->AddObject(Simon->CreateSecondWeapond());
			Simon->whip = nullptr;

		}
	}


}
