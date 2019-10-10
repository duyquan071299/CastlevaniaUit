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
public:
	CPlayScene() { Loadresources(0); };
	void Loadresources(int level);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void Render();
	void Update(DWORD dt);
	unordered_map<int, bool> keys;

};