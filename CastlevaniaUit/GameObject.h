#pragma once
#include"AnimationDatabase.h"

class CGameObject
{
public:

	float x;
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;

	//int state;

	//DWORD dt;

	

public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }

	//int GetState() { return this->state; }

	//void RenderBoundingBox();

	//LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	//void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	/*void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);*/

	//static void AddAnimation(int aniId);

	//CGameObject();

	//virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	//virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	//virtual void SetState(int state) { this->state = state; }


	//~CGameObject();
};
typedef CGameObject *LPGAMEOBJECT;