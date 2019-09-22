#pragma once
#include"GlobalObject.h"
class CScene
{
	CScene() {};
	virtual void Loadresources() {};
	virtual int isKeyDown(int KeyCode) {};
	virtual int isKeyUp(int KeyCode) {};
	virtual void Render() {};
	virtual void Update(DWORD dt) {};
	virtual ~CScene() {};
};