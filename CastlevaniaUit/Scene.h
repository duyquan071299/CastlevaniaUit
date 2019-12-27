#pragma once
#include"GlobalObject.h"
class CScene
{
public:
	CScene() {};
	virtual void OnKeyDown(int KeyCode) { };
	virtual void OnKeyUp(int KeyCode) {  };
	virtual void Loadresources(int level) {};
	virtual void Render() {};
	virtual void Update(DWORD dt) {};
	virtual ~CScene() {};
};