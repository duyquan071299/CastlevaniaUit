#include"PlayScene.h"

void CPlayScene::Loadresources(int level) {
	//SimonSpr = CSpriteDatabase::GetInstance()->GetSprite(PLAYER, 0);
	
	Simon = CSimon::GetInstance();
	Simon->Respawn();
	CurrentMap = new CMap("Resources\\Maps\\scene1.txt", "Resources\\Maps\\Scene_1.png", "Resources\\Maps\\Scene1_Object.txt");
	CCamera::GetInstance()->SetWH(SCREEN_WIDTH, SCREEN_HEIGHT);
	CCamera::GetInstance()->SetPosition(SCREEN_WIDTH / 2,
		SCREEN_HEIGHT / 2);
	//CurrentMap->DrawTileBackground();
	//SimonSprite->Draw(80, 230);
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
	CCamera::GetInstance()->SetPosition(Simon->x - SCREEN_WIDTH / 2 +40, 0);

	CCamera::GetInstance()->Update(CurrentMap->GetMapWidth());
	Simon->Update(dt);
	Simon->HandleKeyboard(keys);
	CurrentMap->Update(dt);
	
	
}

