#pragma once
#include"GameObject.h"


class CDoor :public CGameObject
{
	unordered_map<State, CAnimation*> animations;
	LPANIMATION curAnimation;
	int Width;
	int Height;
	int MoveDistance;
public:
	CDoor() {}
	CDoor(float x, float y);
	
	void SetWH(int width, int height) { Width = width; Height = height; }


	~CDoor() {}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL) {}
	void Render() {
		RenderBoundingBox();
	}

	virtual void GetBoundingBox(float &x, float &y, float &framew, float &frameh) {
		x = this->x;
		y = this->y;
		framew = this->Width;
		frameh = this->Height;
	}
};