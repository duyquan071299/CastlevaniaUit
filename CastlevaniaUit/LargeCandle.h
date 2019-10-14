#pragma once
#include"GameObject.h"

class CLargeCandle:public CGameObject
{
	LPANIMATION animation;
	
public:
	CLargeCandle();
	~CLargeCandle(){}
	void Update(DWORD dt);
	void Render();

};