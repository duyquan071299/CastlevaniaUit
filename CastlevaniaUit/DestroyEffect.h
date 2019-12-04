#pragma once
#include"Effect.h"


class CDestroyEffect :public CEffect
{
	int Type;
public:
	CDestroyEffect();
	CDestroyEffect(float x, float y,int DestroyType);
	void Render();
	void Update(DWORD dt);
};
