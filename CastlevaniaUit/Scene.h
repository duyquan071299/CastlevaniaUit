#pragma once
#include"SimonSprites.h"
#include"GlobalObject.h"
class CScene
{
public:
	CScene() {};
	virtual void Loadresources() {};
	virtual int isKeyDown(int KeyCode) {};
	virtual int isKeyUp(int KeyCode) {};
	virtual void Render() {};
	virtual void Update(DWORD dt) {};
	virtual ~CScene() {};
};