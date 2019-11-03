#include"PlayScene.h"

void CPlayScene::Loadresources(int level) {
	CCamera::GetInstance()->SetWH(SCREEN_WIDTH, SCREEN_HEIGHT);
	CCamera::GetInstance()->SetPosition(SCREEN_WIDTH / 2,
		SCREEN_HEIGHT / 2);
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
		//this->WallObject = CurrentMap->WallObject;
		break;
	}
	case 1:
	{
		Simon->Respawn();
		CurrentMap = new CMap("Resources\\Maps\\Scene2.txt", "Resources\\Maps\\Scene_2.png", "Resources\\Maps\\Scene2_Object.txt");
		this->listObject = CurrentMap->GetListObject();
		//this->WallObject = CurrentMap->WallObject;
	}
	}

};

void CPlayScene::OnKeyDown(int KeyCode)
{
	
	keys[KeyCode] = true;
	Simon->OnKeyDown(KeyCode);
	if (KeyCode == DIK_A)
	{
		delete CurrentMap;
		Loadresources(1);

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
	Simon->Render();
	if (Simon->IsOnAnimation)
	{
		LPSPRITE TileSet = new CSprite(MAP, 0, 1);
		TileSet->Settexture(CTextureDatabase::GetInstance()->GetTexture(HIDING_OBJECT));
		TileSet->SetFrameWH(96, 128);
		TileSet->Draw((float)1408, (float)160, default_color);
	}
	

}

void CPlayScene::Update(DWORD dt)
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
	CCamera::GetInstance()->SetPosition(Simon->x - SCREEN_WIDTH / 2 +40, 0);
	CCamera::GetInstance()->Update(CurrentMap->GetMapWidth());
	if (Simon->isThrowing)
	{
		bool allow=true;
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
	Simon->HandleKeyboard(keys);
	//Simon->Wall(dt, &WallObject);
	Simon->Update(dt, &coObjects);
	


	for (int i = 0; i < coObjects.size(); i++)
	{
		if (dynamic_cast<CLargeCandle *>(coObjects[i]))
		{
			if (coObjects[i]->IsDead == true)
			{
				listObject.push_back(dynamic_cast<CLargeCandle *>(coObjects[i])->GetHolder());
				dynamic_cast<CLargeCandle *>(coObjects[i])->GetHolder()->AppearOnMap();
				listObject.erase(listObject.begin() + i);	
				coObjects.erase(coObjects.begin() + i);
			}
				
		}
		else if (coObjects[i]->IsDead == true && (dynamic_cast<CItem *>(coObjects[i])|| dynamic_cast<CInvisibleObject *>(coObjects[i])))
		{
			listObject.erase(listObject.begin() + i);
		}
		else if (dynamic_cast<CWeapon *>(coObjects[i]))
		{
			if (coObjects[i]->IsDead == true)
			{
				listObject.erase(listObject.begin() + i);
				coObjects.erase(coObjects.begin() + i);

			}

		}
	}
	

	
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
