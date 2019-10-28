#include"Brick.h"
void CBrick::GetBoundingBox(float &x, float &y, float &framew, float &frameh)
{
	x = this->x;
	y = this->y;
	framew = this->Width;
	frameh = this->Height;
}

void CBrick::Render()
{
	RenderBoundingBox();
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects)
{

}