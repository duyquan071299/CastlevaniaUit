#pragma once
#include"GameObject.h"

class CEnemy:public CGameObject
{
protected:
	unordered_map<State, CAnimation*> animations;
	LPANIMATION curAnimation;

public:
	bool isBurning;
	bool isFrozen;
	CEnemy(){}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL){}
	~CEnemy(){}
	void Render(){}
	virtual void GetBoundingBox(float &x, float &y, float &framew, float &frameh){}
	virtual void ChangeAnimation() = 0;

};