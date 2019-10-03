#include"PlayScene.h"

void CPlayScene::Loadresources(int level) {
	//SimonSpr = CSpriteDatabase::GetInstance()->GetSprite(PLAYER, 0);
	Simon = CSimon::GetInstance();
	CurrentMap = new CMap("Resources\\Maps\\scene1.txt", "Resources\\Maps\\Scene_1.png");
	//CurrentMap->DrawTileBackground();
	//SimonSprite->Draw(80, 230);
};

void CPlayScene::OnKeyDown(int KeyCode)
{

}
void  CPlayScene::OnKeyUp(int KeyCode)
{
	
}

void CPlayScene::Render()
{
	CurrentMap->DrawTileBackground();
	
}