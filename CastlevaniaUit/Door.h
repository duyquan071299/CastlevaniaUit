#pragma once
#include"GameObject.h"


class CDoor :public CGameObject
{
	unordered_map<State, CAnimation*> animations;
	LPANIMATION curAnimation;
	State currentstate;
	int Width;
	int Height;
	int MoveDistance;
public:
	CDoor() {}
	CDoor(float x, float y);
	
	void SetWH(int width, int height) { Width = width; Height = height; }
	State GetCurrentState() {
		return currentstate;
	}

	~CDoor() {}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL)
	{
		if (currentstate == OPENNING && curAnimation->GetCurrentFrame()==2)
		{
			ChangeState(OPEN);
		}
		else if (currentstate == CLOSING && curAnimation->GetCurrentFrame() == 2)
		{
			ChangeState(CLOSE);
		}
	}
	void Render() {
		
		
		curAnimation->Render(x, y,default_color);
		
	}

	void ChangeState(State state)
	{
		currentstate = state;
		curAnimation = animations[currentstate];
	}

	virtual void GetBoundingBox(float &x, float &y, float &framew, float &frameh) {
		x = this->x;
		y = this->y;
		framew = this->Width;
		frameh = this->Height;
	}
};