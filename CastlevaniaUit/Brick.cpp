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
	if (this->Type > 2 && this->IsDead == false)
		BrickSprite->Draw(x, y, default_color);
	RenderBoundingBox();
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects)
{

}