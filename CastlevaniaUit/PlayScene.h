#pragma once
#include"Scene.h"
#include "GlobalObject.h"
#include"Simon.h"
#include"Ghost.h"
#include "Map.h"
#include"Panther.h"
class CPlayScene : public CScene
{
private:
	CSimon* Simon;
	CMap* CurrentMap;
	CGhost* Ghost;
	CPanther *Panther;
	int GhostCount;
	int Level;
	int MapBound;
	vector<LPGAMEOBJECT> listObject;
	//vector<LPGAMEOBJECT> WallObject;
public:
	CPlayScene() { Loadresources(0); };
	void Loadresources(int level);
	void UpdateSimon();
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void Render();
	void Update(DWORD dt);
	void GhostRespawn();
	bool IsInCamera(LPGAMEOBJECT object);
	unordered_map<int, bool> keys;

};