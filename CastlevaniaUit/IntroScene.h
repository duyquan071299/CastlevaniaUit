#pragma once
#include"Scene.h"
#include "GlobalObject.h"
#include "Sprites.h"
#include "SpriteDatabase.h"
#include "Map.h"
class CIntroScene: public CScene
{
private:
	CSprite* SimonSprite;
	CMap* CurrentMap;
public:
	CIntroScene() {};
	void Loadresources();
	//int isKeyDown(int KeyCode) {};
	int isKeyUp(int KeyCode) { return 0; };
	void Render() {};
	void Update(DWORD dt) {};

};