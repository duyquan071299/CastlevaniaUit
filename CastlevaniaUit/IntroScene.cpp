#include"IntroScene.h"

void CIntroScene::Loadresources() {
	
		
};

CIntroScene::CIntroScene()
{

	BackGround = CSpriteDatabase::GetInstance()->GetSprite(MAIN_MENU, 0);
	BackGroundCastle = CAnimationDatabase::GetInstance()->Get(INTRO_ANI, ACTIVE);
	Scoreboard = new CScoreBoard(0.0f,0.0f);
	IsInMainMenu = true;
}

void CIntroScene::Render()
{
	
	BackGround->DrawScoreBoard(MAIN_MENU_POS_X, MAIN_MENU_POS_Y, default_color);
	if (IsInMainMenu == true)
		BackGroundCastle->Render(ANI_POS_X, ANI_POS_Y, default_color);
	else
	{
		
		Scoreboard->Render();
		for (int i = 0; i < ListObject.size(); i++)
			ListObject.at(i)->Render();
	}
		
	
}

void CIntroScene::OnKeyDown(int KeyCode)
{

	if (KeyCode == DIK_A)
	{
		IsInMainMenu = false;
		BackGround = CSpriteDatabase::GetInstance()->GetSprite(INTROSCENE, 0);
		ListObject.push_back(new CIntroObject(400.0f, 120.0f, -0.01f, 0, 1));
		ListObject.push_back(new CIntroObject(250.0f, 100.0f, -0.01f, -0.005, 0));
		ListObject.push_back(new CIntroObject(50.0f, 200.0f, 0.03f, -0.02, 0));
	}
}

void  CIntroScene::OnKeyUp(int KeyCode)
{
	
}

void CIntroScene::Update(DWORD dt)
{
	for (int i = 0; i < ListObject.size(); i++)
		ListObject.at(i)->Update(dt);
}