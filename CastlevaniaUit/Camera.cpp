#include "Camera.h"


CCamera* CCamera::instance = NULL;

CCamera* CCamera::GetInstance()
{
	if (instance == NULL)
		instance = new CCamera();
	return instance;
}

CCamera::CCamera()
{
	this->Width = SCREEN_WIDTH;
	this->Height = SCREEN_HEIGHT;
}


RECT CCamera::GetBound()
{
	RECT bound;

	bound.left = (long)this->x;
	bound.right = (long)this->x + Width;
	bound.top = (long)this->y;
	bound.bottom = (long)(this->y + Height);

	return bound;
}

