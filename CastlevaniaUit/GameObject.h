#pragma once
#include"AnimationDatabase.h"
#include <algorithm>

class CGameObject;
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};





class CGameObject
{
public:

	float x;
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	float PrevX;
	float PrevY;
	
	bool IsDead=false;
	bool isColiable;
	bool isIncamera;
	
	int nx;

	//int state;

	DWORD dt;


public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }

	
	void RenderBoundingBox();

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);

	

	virtual void GetBoundingBox(float &x, float &y, float &framew, float &frameh) = 0;
	RECT GetBBox()
	{
		float x,y,width, height;
		GetBoundingBox(x, y, width, height);
		RECT Bbox;
		Bbox.left = (long)x;
		Bbox.top = (long)y;
		Bbox.right = (long)(x + width);
		Bbox.bottom = (long)(y + height);
		return  Bbox;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects=NULL);
	virtual void Render() = 0;
	bool IsInCamera()
	{
		float x, y, framew, frameh;
		this->GetBoundingBox(x, y, framew, frameh);
		RECT objRECT;
		objRECT.left =(long)x;
		objRECT.top = (long)y;
		objRECT.right = objRECT.left + (long)framew;
		objRECT.bottom = objRECT.top + (long)frameh;
		RECT Camera = CCamera::GetInstance()->GetBound();
		if (objRECT.left >Camera.right || objRECT.right < Camera.left|| objRECT.top >Camera.bottom|| objRECT.bottom < Camera.top)
		{
			return false;
		}

		return true;

	}

	//~CGameObject();
};
