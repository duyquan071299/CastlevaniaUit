#pragma once
#include"SimonSprites.h"
#include"GlobalObject.h"
class CScene
{
public:
	CScene() {};
	virtual void Loadresources() {};
	virtual int isKeyDown(int KeyCode) { return 0; };
	virtual int isKeyUp(int KeyCode) { return 0; };
	virtual void Render() {};
	virtual void Update(DWORD dt) {};
	virtual ~CScene() {};
};