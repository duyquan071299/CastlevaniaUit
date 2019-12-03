#pragma once
#include"Scene.h"
#include "GlobalObject.h"
#include"Simon.h"
#include"Ghost.h"
#include "Map.h"
#include"Enemy.h"
#include"Panther.h"
#include"Kappa.h"
#include"Bat.h"
#include"Door.h"
#include"Grid.h"
#include"ScoreBoard.h"
#include"Effect.h"
class CPlayScene : public CScene
{
private:
	CSimon* Simon;
	CScoreBoard * ScoreBoard;
	CMap* CurrentMap;
	CPanther *Panther;
	CDoor *Door;
	int GhostCount;
	CGrid * Grid;
	int BatCount;
	int KappaCount;
	int PantherCount=3;
	int PantherAtX1=1;
	int PantherAtX2=1;
	int PantherAtX3=1;
	int Level;
	int MapBoundLeft;
	int MapBoundRight;
	int UnderGroundMapBoundLeft=3136;
	int UnderGroundMapBoundRight=4160;
	bool isThroughDoorOne;
	DWORD TimeBetWeenGhostRespawn;
	DWORD TimeBetWeenBatRespawn;
	DWORD TimeBetWeenKappaRespawn;
	bool AllowRespawnKappa;
	bool AllowRespawnGhost;
	bool AllowRespawnBat;
	bool SetUpTime=true;
	bool FirstRespawn;
	DWORD TimeLimit;
	DWORD FrozenTime;
	DWORD CrossTime;
	
public:
	CPlayScene() { Loadresources(0); };
	void Loadresources(int level);
	void UpdateSimon();
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void Render();
	void Update(DWORD dt);
	void DrawHiddenObject();
	unordered_map<int, bool> keys;
	

};