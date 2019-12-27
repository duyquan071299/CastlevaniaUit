#pragma once
#include"Scene.h"
#include "GlobalObject.h"
#include "Sprites.h"
#include"ScoreBoard.h"
#include"IntroObject.h"
#include "SpriteDatabase.h"
#include"Simon.h"
#define ANI_POS_X 330.0f
#define ANI_POS_Y 195.0f
#define SIMON_START_POS_X 480.0f
#define SIMON_START_POS_Y 338.0f
#define SIMON_END_POS 227.0f
#define SIMON_START_SPEED - 0.08f


class CIntroScene: public CScene
{
private:
	bool IsInMainMenu;
	CScoreBoard* Scoreboard;
	LPANIMATION SimonSprite;
	CSimon *Simon;
	LPSPRITE BackGround;
	LPANIMATION BackGroundCastle;
	string BackGroundText;
	vector<CIntroObject *> ListObject;
	DWORD StarGameTime;
	DWORD IntroSceneTime;
	DWORD TimeToDrawText;
	DWORD TimeToGame;
	bool isPushStartGame;
	bool isDrawText;

public:
	CIntroScene();
	~CIntroScene();
	void Loadresources(int level);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void Render();
	void Update(DWORD dt);
	void SetUpSimon();
	void SetUpObject();

};