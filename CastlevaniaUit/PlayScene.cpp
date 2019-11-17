#include"PlayScene.h"
#include"SimonStateWalking.h"


void CPlayScene::Loadresources(int level) {
	CCamera::GetInstance()->SetWH(SCREEN_WIDTH, SCREEN_HEIGHT);
	CCamera::GetInstance()->SetPosition(SCREEN_WIDTH / 2,
		SCREEN_HEIGHT / 2);

	for (int i = 0; i < listObject.size(); i++)
	{
		delete listObject[i];
	}
	this->listObject.clear();
	//this->WallObject.clear();
	Simon = CSimon::GetInstance();

	switch (level)
	{
	case 0:
	{
		Simon->Respawn();
		CurrentMap = new CMap("Resources\\Maps\\Scene1.txt", "Resources\\Maps\\Scene_1.png", "Resources\\Maps\\Scene1_Object.txt");
		this->listObject = CurrentMap->GetListObject();
		MapBoundRight= CurrentMap->GetMapWidth();
		MapBoundLeft = 0;
		Simon->x = 1430;
		this->Level = level;
		Simon->AtLevel = level;
		break;
	}
	case 1:
	{
		Simon->Respawn();
		CurrentMap = new CMap("Resources\\Maps\\Scene2.txt", "Resources\\Maps\\Scene_2.png", "Resources\\Maps\\Scene2_Object.txt");
		this->listObject = CurrentMap->GetListObject();
		Door = new CDoor(3056, 32);
		Simon->x =0;
		Simon->y = 0;
		this->Level = level;
		Simon->AtLevel = level;
		MapBoundLeft = 0;
		MapBoundRight = 3072;
		MapBoundRight = 5000;

		//GhostRespawn();
	}
	}
	

};

void CPlayScene::OnKeyDown(int KeyCode)
{
	if (!Simon->IsFreeze && !Simon->IsOnAnimation)
	{
		keys[KeyCode] = true;
		Simon->OnKeyDown(KeyCode);
		if (KeyCode == DIK_A)
		{
			delete CurrentMap;
			Loadresources(1);
			


		}
		else if (KeyCode == DIK_B)
		{
			Panther->isRunning = true;
			Panther->isSitting = false;
			Panther->ChangeAni();
		}
		else if (KeyCode == DIK_Q)
		{
			GhostRespawn();
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
	

	for (int i = 0; i < listObject.size(); i++)
	{
		if(!IsInCamera(listObject[i]))
		{
			if (dynamic_cast<CWeapon *>(listObject[i]))
			{
				listObject[i]->IsDead = true;
				listObject.erase(listObject.begin() + i);
				
			}
				
			continue;
		}
		
		listObject[i]->Render();
	}
	if (Door != nullptr)
		Door->Render();

	Simon->Render();
	if ((Simon->IsOnAnimation||Simon->IsRespawn)&&Simon->vx>0&&!this->Level)
	{
		LPSPRITE TileSet = new CSprite(MAP, 0, 1);
		TileSet->Settexture(CTextureDatabase::GetInstance()->GetTexture(HIDING_OBJECT));
		TileSet->SetFrameWH(96, 128);
		TileSet->Draw((float)1408, (float)160, default_color);
	}
	

}

void CPlayScene::Update(DWORD dt)
{
	if (this->Level == 1)
	{
		if (CCamera::GetInstance()->isWithSimon)
		{
			if (Simon->y < SCREEN_HEIGHT - 100)
			{
				CCamera::GetInstance()->SetPosition(Simon->x - SCREEN_WIDTH / 2 + 40, 0);
				CCamera::GetInstance()->Update(MapBoundLeft, MapBoundRight);
			}
			else
			{

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
					MapBoundRight = 6000;
					CCamera::GetInstance()->isWithSimon = true;
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
	

	UpdateSimon();
	for (int i = 0; i < listObject.size(); i++)
	{
		if (dynamic_cast<CKappa *>(listObject[i]))
		{
			if (dynamic_cast<CKappa *>(listObject[i])->isAtacking && dynamic_cast<CKappa *>(listObject[i])->isFire == false)
			{
				dynamic_cast<CKappa *>(listObject[i])->isFire = true;
				listObject.push_back(new CEnemyBullet(listObject[i]->x, listObject[i]->y+10, listObject[i]->nx));
			}
			
		}
			

	}

	/*if (GhostCount == 0 && this->Level)
		GhostRespawn();*/
	

	vector<LPGAMEOBJECT> coObjects;
	
	for (int i = 0; i < listObject.size(); i++)
	{
		if (!IsInCamera(listObject[i]))
			listObject[i]->isIncamera = false;
		else
			listObject[i]->isIncamera = true;
		coObjects.push_back(listObject[i]);
	}
	for (int i = 0; i < listObject.size(); i++)
	{
		listObject[i]->Update(dt, &coObjects);

	}	


	for (int i = 0; i < coObjects.size(); i++)
	{
		if (dynamic_cast<CCandle *>(coObjects[i]))
		{
			if (coObjects[i]->IsDead == true)
			{
				listObject.push_back(dynamic_cast<CCandle *>(coObjects[i])->GetHolder());
				dynamic_cast<CCandle *>(coObjects[i])->GetHolder()->AppearOnMap();
				listObject.erase(listObject.begin() + i);	
				coObjects.erase(coObjects.begin() + i);
			}
				
		}
		else if(coObjects[i]->IsDead && !dynamic_cast<CBrick*>(coObjects[i]))
		{
			if (dynamic_cast<CGhost *>(coObjects[i]))
			{
				GhostCount--;
			}
			listObject.erase(listObject.begin() + i);
			coObjects.erase(coObjects.begin() + i);
		}
		
		
	}
	if (!Simon->IsFreeze)
	{
		if(!Simon->IsOnAnimation)
			Simon->HandleKeyboard(keys);
		Simon->Update(dt, &coObjects);
	}
	if (Door != nullptr)
		Door->Update(dt, &coObjects);
	CurrentMap->Update(dt);
	
	
}


bool CPlayScene::IsInCamera(LPGAMEOBJECT object)
{
	float x, y, framew, frameh;
	object->GetBoundingBox(x, y, framew, frameh);
	RECT objRECT;
	objRECT.left = x;
	objRECT.top = y;
	objRECT.right = objRECT.left + framew;
	objRECT.bottom = objRECT.top + frameh;
	if (!CurrentMap->isContain(objRECT, CCamera::GetInstance()->GetBound()))
	{
		return false;

	}
	return true;
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

	if (Simon->y < SCREEN_HEIGHT - 100)
	{
		if (Simon->vx < 0 && Simon->x < MapBoundLeft - 9)
			Simon->x = MapBoundLeft - 10;
		else if(Simon->vx>=0 && Simon->x > MapBoundRight -48)
			Simon->x = MapBoundRight - 48;
			
	}
	else
	{
		if (Simon->vx < 0 && Simon->x < UnderGroundMapBoundLeft - 9)
			Simon->x = UnderGroundMapBoundLeft - 10;
	}


	if (Simon->isThrowing)
	{
		bool allow = true;
		for (int i = 0; i < listObject.size(); i++)
		{
			if (dynamic_cast<CWeapon *>(listObject[i]))
				allow = false;

		}
		if (allow&&Simon->SecondWeapon->IsDead == false)
		{
			listObject.push_back(Simon->SecondWeapon);

		}
	}


}

void CPlayScene::GhostRespawn()
{
	/*for (int i = 0; i < 3; i++)
	{
		Ghost = new CGhost();
		Ghost->SetPosition(CCamera::GetInstance()->x+SCREEN_WIDTH+i*30, 255);
		Ghost->Respawn(-1);
		GhostCount++;
		listObject.push_back(Ghost);
	}*/

	Bat = new CBat();
	Bat->SetPosition(CCamera::GetInstance()->x + SCREEN_WIDTH -70, 270);
	Bat->Respawn(-1);
	listObject.push_back(Bat);
	/*Panther = new CPanther();
	Panther->SetPosition(1376, 159);
	Panther->Respawn(-1);
	listObject.push_back(Panther);*/

	//Panther = new CPanther();
	//Panther->SetPosition(1860, 159);
	//Panther->Respawn(-1);
	//listObject.push_back(Panther);

	//Panther = new CPanther();
	//Panther->SetPosition(1772, 95);
	//Panther->Respawn(-1);
	//listObject.push_back(Panther);
}