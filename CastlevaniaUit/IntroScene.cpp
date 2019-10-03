#include"IntroScene.h"

void CIntroScene::Loadresources() {
	SimonSprite = CSpriteDatabase::GetInstance()->GetSprite(PLAYER,0);
	
	CurrentMap = new CMap("Resources\\Maps\\scene1.txt", "Resources\\Maps\\Scene_1.png");
	CurrentMap->DrawTileBackground();
	SimonSprite->Draw(80, 230);
		
};