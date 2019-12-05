#include"IntroScene.h"
#include"SimonStateWalking.h"
#include"SceneManager.h"
#include"PlayScene.h"
void CIntroScene::Loadresources() {
	
		
};

CIntroScene::CIntroScene()
{

	BackGround = CSpriteDatabase::GetInstance()->GetSprite(MAIN_MENU, 0);
	BackGroundCastle = CAnimationDatabase::GetInstance()->Get(INTRO_ANI, ACTIVE);
	Scoreboard = new CScoreBoard(0.0f,0.0f);
	IsInMainMenu = true;
	BackGroundText = "PUSH START KEY";
	isDrawText = true;
}

void CIntroScene::Render()
{
	
	BackGround->DrawScoreBoard(MAIN_MENU_POS_X, MAIN_MENU_POS_Y, default_color);
	if (IsInMainMenu == true)
	{
		if (isDrawText == true)
		{
			float PosPostion = 140;
			for (int i = 0; i < this->BackGroundText.length(); i++)
			{
				if (BackGroundText.at(i) == 32)
					continue;
				if (i != 0 && BackGroundText.at(i - 1) == 32)
				{
					PosPostion += 25;
				}
				CSpriteDatabase::GetInstance()->GetSprite(FONT, BackGroundText.at(i) - 55)->DrawScoreBoard(PosPostion, 270, default_color);
				PosPostion += 14;

			}
		}
		
		if (isPushStartGame)
			BackGroundCastle->GetCurrenrFrame()->Draw(ANI_POS_X, ANI_POS_Y, default_color);
		else
			BackGroundCastle->Render(ANI_POS_X, ANI_POS_Y, default_color);
	}
	else
	{
		
		Scoreboard->Render();
		for (int i = 0; i < ListObject.size(); i++)
			ListObject.at(i)->Render();
		Simon->Render();
	}
		
	
}

void CIntroScene::OnKeyDown(int KeyCode)
{

	if (KeyCode == DIK_A)
	{
		
		StarGameTime = GetTickCount();
		isPushStartGame = true;
		TimeToDrawText = GetTickCount();
		

	}
}

void  CIntroScene::OnKeyUp(int KeyCode)
{
	
}

void CIntroScene::Update(DWORD dt)
{
	for (int i = 0; i < ListObject.size(); i++)
		ListObject.at(i)->Update(dt);
	if (IsInMainMenu == true)
	{
		if (GetTickCount() - StarGameTime >= 3000 && StarGameTime != 0)
		{
			IsInMainMenu = false;

			BackGround = CSpriteDatabase::GetInstance()->GetSprite(INTROSCENE, 0);
			SetUpObject();
			StarGameTime = 0;
			SetUpSimon();

		}
		if (GetTickCount() - TimeToDrawText >= 200 && TimeToDrawText != 0)
		{
			isDrawText = !isDrawText;
			TimeToDrawText = GetTickCount();
		}
	}
	else
	{
		if (GetTickCount() - TimeToGame >= 2500 && TimeToGame != 0)
		{
			CSceneManager::GetInstance()->LoadScene(new CPlayScene());
			TimeToGame = 0;
			return;
		}

		Simon->x += Simon->vx * dt;
		if (Simon->x <= SIMON_END_POS && Simon->vx!=0)
		{
			Simon->ChangeState(new CSimonStateStanding(FACING_INSIDE));
			Simon->vx = 0;
			TimeToGame = GetTickCount();
			
		}
	}
	
}

void CIntroScene::SetUpSimon()
{
	Simon = new CSimon();
	Simon->ChangeState(new CSimonStateWalking(WALKING_LEFT));
	Simon->vx = SIMON_START_SPEED;
	Simon->y = SIMON_START_POS_Y;
	Simon->x = SIMON_START_POS_X;
}

void CIntroScene::SetUpObject()
{
	ListObject.push_back(new CIntroObject(400.0f, 120.0f, -0.01f, 0, 1));
	ListObject.push_back(new CIntroObject(250.0f, 100.0f, -0.01f, -0.005, 0));
	ListObject.push_back(new CIntroObject(50.0f, 200.0f, 0.03f, -0.02, 0));
}

CIntroScene::~CIntroScene()
{
	if (Simon)
		delete Simon;
	Simon = nullptr;
	if (Scoreboard)
		delete Scoreboard;
	Scoreboard = nullptr;
}

