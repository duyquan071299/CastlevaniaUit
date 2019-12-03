#pragma once
#include"Effect.h"


class CBubbleEffect :public CEffect
{

public:
	CBubbleEffect();
	CBubbleEffect(float x, float y, float vx, float vy);
	void Render();
	void Update(DWORD dt);
};