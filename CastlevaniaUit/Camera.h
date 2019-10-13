#pragma once
#include "GlobalObject.h"

class CCamera
{
private:
	static CCamera* instance;

	int Width, Height;
	

public:

	static CCamera* GetInstance();
	float x, y;
	CCamera();
	//void SetPosition();
	void SetPosition(float x, float y) {
		this->x = x;
		this->y = y;
	}
	//void SetPosition(D3DXVECTOR3 pos);
	void SetWH(int width, int height)
	{
		this->Width = width;
		this->Height = height;
	}
	int GetWidth() { return Width; }
	int GetHeight() {
		return Height;
	};
	void Update(int MapWidth)
	{
		if (this->x < 0)
		{
			this->x = 0;
		}
		else if (this->x > MapWidth-this->Width+16)
		{
			this->x = (float)MapWidth - this->Width+16;
		}
	}
	//D3DXVECTOR3 GetPosition() { return Position; }
	RECT GetBound();

	/*void Update(RECT MapRect);
	void ConvertPosInViewPort(float& x, float& y);*/
};