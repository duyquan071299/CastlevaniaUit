#include"Brick.h"
void CBrick::GetBoundingBox(float &x, float &y, float &framew, float &frameh)
{
	x = this->x;
	y = this->y;
	framew = frameh = 32;
}

void CBrick::Render()
{
	Sprite->Draw(x, y);
	RenderBoundingBox();
}