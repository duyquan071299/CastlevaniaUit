#include"BubbleEffect.h"



void CBubbleEffect::Update(DWORD dt)
{
	this->x += vx * dt;
	this->y += vy * dt;
	vy += 0.0015f*dt;
	if (this->EffectSprite->IsLastFrame() == true)
		this->isDone = true;
}

CBubbleEffect::CBubbleEffect()
{

}
CBubbleEffect::CBubbleEffect(float x, float y, float vx, float vy)
{
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	this->EffectSprite = new CAnimation(300);
	this->EffectSprite->Add(EFFECT, 5, 1000);

}
void CBubbleEffect::Render()
{
	this->EffectSprite->Render(x, y, default_color);

}