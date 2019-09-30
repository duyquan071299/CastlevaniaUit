#include"IntroScene.h"

void CIntroScene::Loadresources() {
	SimonSprite = CSpriteDatabase::GetInstance()->GetSprite(PLAYER);
	SimonSprite->Draw(100, 100);
	CurrentMap = new CMap("Resources\\Maps\\scene1.tmx");
	//CurrentMap->DrawTileBackground();
		
};