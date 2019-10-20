#include"PlayScene.h"

void CPlayScene::Loadresources(int level) {
	
	Simon = CSimon::GetInstance();
	Simon->Respawn();
	CurrentMap = new CMap("Resources\\Maps\\scene1.txt", "Resources\\Maps\\Scene_1.png", "Resources\\Maps\\Scene1_Object.txt");
	CCamera::GetInstance()->SetWH(SCREEN_WIDTH, SCREEN_HEIGHT);
	CCamera::GetInstance()->SetPosition(SCREEN_WIDTH / 2,
		SCREEN_HEIGHT / 2);
	this->listObject = CurrentMap->GetListObject();
};

void CPlayScene::OnKeyDown(int KeyCode)
{
	
	keys[KeyCode] = true;
	Simon->OnKeyDown(KeyCode);
	
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
		float x, y, framew, frameh;
		listObject[i]->GetBoundingBox(x, y, framew, frameh);
		RECT objRECT;
		objRECT.left = x;
		objRECT.top = y;
		objRECT.right = objRECT.left + framew;
		objRECT.bottom = objRECT.top + frameh;
		if (!CurrentMap->isContain(objRECT, CCamera::GetInstance()->GetBound()))
		{
			if (dynamic_cast<CWeapon *>(listObject[i]))
			{
				listObject.erase(listObject.begin() + i);
				Simon->isThrowing = false;
			}
				
			continue;
		}
		
			

		listObject[i]->Render();
	}
	Simon->Render();
	//CCamera::GetInstance()->SetPosition(CCamera::GetInstance()->GetPosition() + D3DXVECTOR3(10, 0, 0));

}

void CPlayScene::Update(DWORD dt)
{
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
		if (allow)
		{
			listObject.push_back(Simon->SecondWeapon);
			Simon->SecondWeapon->IsDead = false;
		}
			
		
	}

	vector<LPGAMEOBJECT> coObjects;
	for (int i = 0; i < listObject.size(); i++)
	{
		coObjects.push_back(listObject[i]);
	}
	for (int i = 0; i < listObject.size(); i++)
	{
		listObject[i]->Update(dt, &coObjects);

	}	
	Simon->HandleKeyboard(keys);
	Simon->Update(dt, &coObjects);


	for (int i = 0; i < coObjects.size(); i++)
	{
		if (dynamic_cast<CLargeCandle *>(coObjects[i]))
		{
			if (coObjects[i]->IsDead == true)
			{
				listObject.push_back(dynamic_cast<CLargeCandle *>(coObjects[i])->GetHolder());
				listObject.erase(listObject.begin() + i);	
				coObjects.erase(coObjects.begin() + i);
			}
				
		}
		else if (dynamic_cast<CWeapon *>(coObjects[i]))
		{
			if (coObjects[i]->IsDead == true)
			{
				listObject.erase(listObject.begin() + i);
				coObjects.erase(coObjects.begin() + i);
				Simon->isThrowing = false;
			}
			
		}
		else if (coObjects[i]->IsDead == true && dynamic_cast<CItem *>(coObjects[i]))
		{
			listObject.erase(listObject.begin() + i);
		}
			
	}
	

	
	CurrentMap->Update(dt);
	
	
}

