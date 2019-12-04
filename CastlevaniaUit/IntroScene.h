#pragma once
#include"Scene.h"
#include "GlobalObject.h"
#include "Sprites.h"
#include"ScoreBoard.h"
#include"IntroObject.h"
#include "SpriteDatabase.h"
#define MAIN_MENU_POS_X -17.0f
#define MAIN_MENU_POS_Y 0.0f
#define ANI_POS_X 320.0f
#define ANI_POS_Y 195.0f

class CIntroScene: public CScene
{
private:
	bool IsInMainMenu;
	CScoreBoard* Scoreboard;
	LPANIMATION SimonSprite;
	LPSPRITE BackGround;
	LPANIMATION BackGroundCastle;
	LPSPRITE BackGroundText;
	vector<CIntroObject *> ListObject;

public:
	CIntroScene();
	void Loadresources();
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void Render();
	void Update(DWORD dt);


};