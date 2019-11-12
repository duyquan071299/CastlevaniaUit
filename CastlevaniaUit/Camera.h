#pragma once
#include "GlobalObject.h"

class CCamera
{
private:
	static CCamera* instance;

	int Width, Height;
	

public:

	bool isWithSimon=true;
	static CCamera* GetInstance();
	float x, y;
	CCamera();

	void SetPosition(float x, float y) {
		this->x = x;
		this->y = y;
	}

	void SetWH(int width, int height)
	{
		this->Width = width;
		this->Height = height;
	}
	int GetWidth() { return Width; }
	int GetHeight() {
		return Height;
	};
	void Update(int MapBoundLeft,int MapBoundRight)
	{
		if (this->x < MapBoundLeft)
		{
			this->x = MapBoundLeft;
		}
		else if (this->x > MapBoundRight -this->Width+16)
		{
			this->x = (float)MapBoundRight - this->Width+16;
		}
	}
	
	RECT GetBound();


};