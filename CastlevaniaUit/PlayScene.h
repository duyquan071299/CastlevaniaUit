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
class CPlayScene : public CScene
{
private:
	CSimon* Simon;
	CMap* CurrentMap;
	CPanther *Panther;
	CDoor *Door;
	int GhostCount;
	int BatCount;
	int KappaCount;
	int Level;
	int MapBoundLeft;
	int MapBoundRight;
	int UnderGroundMapBoundLeft=3136;
	int UnderGroundMapBoundRight=4160;
	vector<CEnemy*> listEnemy;
	vector<LPGAMEOBJECT> listObject;
	vector<CEnemyBullet*> listEnemyBullet;
	DWORD TimeBetWeenGhostRespawn;
	DWORD TimeBetWeenBatRespawn;
	DWORD TimeBetWeenKappaRespawn;
	bool AllowRespawnKappa;
	bool AllowRespawnGhost;
	bool AllowRespawnBat;
	bool SetUpTime=true;
	bool FirstRespawn;
	DWORD TimeLimit;
	//vector<LPGAMEOBJECT> WallObject;
public:
	CPlayScene() { Loadresources(0); };
	void Loadresources(int level);
	void UpdateSimon();
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void Render();
	void Update(DWORD dt);
	bool IsInCamera(LPGAMEOBJECT object);
	unordered_map<int, bool> keys;

};