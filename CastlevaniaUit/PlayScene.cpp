#include"PlayScene.h"

void CPlayScene::Loadresources(int level) {
	//SimonSpr = CSpriteDatabase::GetInstance()->GetSprite(PLAYER, 0);
	Simon = CSimon::GetInstance();
	Simon->Respawn();
	CurrentMap = new CMap("Resources\\Maps\\scene1.txt", "Resources\\Maps\\Scene_1.png");
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
	CurrentMap->DrawTileBackground();
	Simon->Render();
}

void CPlayScene::Update(DWORD dt)
{
	Simon->Update(dt);
	Simon->HandleKeyboard(keys);
	


}

