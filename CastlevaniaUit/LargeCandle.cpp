#include"LargeCandle.h"

CLargeCandle::CLargeCandle()
{
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
}