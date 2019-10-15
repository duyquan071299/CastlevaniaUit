#include"LargeCandle.h"

CLargeCandle::CLargeCandle()
{
	type = LARGE_CANDLE;
	animation = new CAnimation(100);
	animation->Add(CANDLE, 0);
	animation->Add(CANDLE, 1);
}

void CLargeCandle::Update(DWORD dt)
{

}
void CLargeCandle::Render()
{
	animation->Render(x, y);
	RenderBoundingBox();
}

void CLargeCandle::GetBoundingBox(float &x, float &y, float &framew, float &frameh)
{
	x = this->x;
	y = this->y;
	framew = 32;
	frameh = 64;

}