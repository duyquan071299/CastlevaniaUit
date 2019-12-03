#include"Candle.h"

CCandle::CCandle(float x, float y,HolderType HolderType, int CandleType)
{
	animation = new CAnimation(100);
	switch (CandleType)
	{	
	case 1:
		animation->Add(CANDLE, 0);
		animation->Add(CANDLE, 1);
		break;
	case 2:
		animation->Add(CANDLE, 2);
		animation->Add(CANDLE, 3);
	}
	HDType = HolderType;
	SetPosition(x, y);
	isColiable = true;
	this->isIncamera = true;

}

void CCandle::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects)
{
		
}
void CCandle::Render()
{
	if (animation->IsLastFrame()==true && animation->GetFrameSize() == 3)
	{
		IsDead = true;
	}
	if(!isBurning)
		RenderBoundingBox();
	animation->Render(x, y, default_color);
	if (animation->GetCurrentFrame() >=0 && animation->GetCurrentFrame() < animation->GetFrameSize() - 1 && animation->GetFrameSize() == 3)
	{
		LPANIMATION ani = new CAnimation(80);
		ani->Add(EFFECT, 3);
		ani->Render(x, y, default_color);
	}

}

void CCandle::GetBoundingBox(float &x, float &y, float &framew, float &frameh)
{
	x = this->x;
	y = this->y;
	framew = (float)Width;
	frameh = (float)Height;

}
void CCandle::ChangeAnimation()
{
	this->isBurning = true;
	animation = new CAnimation(80);
	animation->Add(EFFECT, 0);
	animation->Add(EFFECT, 1);
	animation->Add(EFFECT, 2);
	
}