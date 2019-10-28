#pragma once
#include"Scene.h"
#include "GlobalObject.h"
#include"Simon.h"
#include "Map.h"
class CPlayScene : public CScene
{
private:
	CSimon* Simon;
	CMap* CurrentMap;
	vector<LPGAMEOBJECT> listObject;
	//vector<LPGAMEOBJECT> WallObject;
public:
	CPlayScene() { Loadresources(0); };
	void Loadresources(int level);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void Render();
	void Update(DWORD dt);
	bool IsInCamera(LPGAMEOBJECT object);
	unordered_map<int, bool> keys;

};