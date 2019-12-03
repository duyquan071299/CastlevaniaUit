#pragma once
#include"Effect.h"


class CBrokenBrickEffect:public CEffect
{ 
	
public:
	CBrokenBrickEffect();
	CBrokenBrickEffect(float x, float y, float vx, float vy);
	void Render();
	void Update(DWORD dt);
};