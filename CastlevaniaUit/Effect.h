#pragma once
#include"GameObject.h"


class CEffect
{
protected:
	LPANIMATION EffectSprite;
	float x, y;
	float vx, vy;
	bool isDone;
public:
	CEffect() {};
	~CEffect() {};
	bool CheckIsDone() { return isDone; }
	virtual void Render() = 0;
	virtual void Update(DWORD dt)=0;

};