#include"PlayScene.h"

void CPlayScene::Loadresources(int level) {
	
	Simon = CSimon::GetInstance();
	Simon->Respawn();
	CurrentMap = new CMap("Resources\\Maps\\scene1.txt", "Resources\\Maps\\Scene_1.png", "Resources\\Maps\\Scene1_Object.txt");
	CCamera::GetInstance()->SetWH(512, SCREEN_HEIGHT);
	CCamera::GetInstance()->SetPosition(512 / 2,
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
	Simon->Render();
	//CCamera::GetInstance()->SetPosition(CCamera::GetInstance()->GetPosition() + D3DXVECTOR3(10, 0, 0));

}

void CPlayScene::Update(DWORD dt)
{
	CCamera::GetInstance()->SetPosition(Simon->x - 512 / 2 +40, 0);
	CCamera::GetInstance()->Update(CurrentMap->GetMapWidth());
	//listObject.push_back

	vector<LPGAMEOBJECT> coObjects;
	for (int i = 0; i < listObject.size(); i++)
	{
		coObjects.push_back(listObject[i]);
	}

	for (int i = 0; i < listObject.size(); i++)
	{
		listObject[i]->Update(dt, &coObjects);
	}


	Simon->Update(dt, &coObjects);
	Simon->HandleKeyboard(keys);
	CurrentMap->Update(dt);
	
	
}

