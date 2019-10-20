#include"LargeCandle.h"

CLargeCandle::CLargeCandle(int x, int y,HolderType HolderType)
{
	animation = new CAnimation(100);
	animation->Add(CANDLE, 0);
	animation->Add(CANDLE, 1);
	Holder = new CItem(HolderType);
	SetPosition(x, y);
	Holder->x = this->x + 8;
	Holder->y = this->y;


}

void CLargeCandle::Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects)
{
		
}
void CLargeCandle::Render()
{
	if (animation->IsLastFrame()==true && animation->GetFrameSize() == 3)
	{
		IsDead = true;
	}
	animation->Render(x, y);	
	if (animation->GetCurrentFrame() >=0 && animation->GetCurrentFrame() < animation->GetFrameSize() - 1 && animation->GetFrameSize() == 3)
	{
		LPANIMATION ani = new CAnimation(80);
		ani->Add(EFFECT, 3);
		ani->Render(x, y);
	}
	RenderBoundingBox();
}

void CLargeCandle::GetBoundingBox(float &x, float &y, float &framew, float &frameh)
{
	x = this->x;
	y = this->y;
	framew = 32;
	frameh = 64;

}
void CLargeCandle::ChangeAnimation()
{
	animation = new CAnimation(80);
	animation->Add(EFFECT, 0);
	animation->Add(EFFECT, 1);
	animation->Add(EFFECT, 2);
	
}