#pragma once
#include"Scene.h"
#include "GlobalObject.h"
#include "Sprites.h"
#include "SpriteFactory.h"

class CIntroScene: public CScene
{
private:
	CSprite* SimonSprite;
public:
	CIntroScene() {};
	void Loadresources() {};
	//int isKeyDown(int KeyCode) {};
	int isKeyUp(int KeyCode) {};
	void Render() {};
	void Update(DWORD dt) {};

};