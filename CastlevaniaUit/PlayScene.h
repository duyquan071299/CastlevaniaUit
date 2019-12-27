#pragma once
#include"Scene.h"
#include "GlobalObject.h"
#include"Simon.h"
#include "Map.h"
#include"Grid.h"
#include"ScoreBoard.h"
#include"Effect.h"
#include"StageManager.h"
#define INDOOR 1
#define OUTDOOR 0
#define LOADING_TIME 2000

class CPlayScene : public CScene
{
private:
	CSimon* Simon;
	CScoreBoard * ScoreBoard;
	CMap* CurrentMap;
	CGrid * Grid;
	DWORD FrozenTime;
	DWORD CrossTime;
	DWORD RespawnTime;
public:
	CPlayScene() { };
	void Loadresources(int level);
	void UpdateSimon();
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void Render();
	void Reset();
	void Update(DWORD dt);
	unordered_map<int, bool> keys;
	

};