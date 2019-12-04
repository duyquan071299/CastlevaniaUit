#include"DestroyEffect.h"



void CDestroyEffect::Update(DWORD dt)
{

	if (this->EffectSprite->IsLastFrame() == true)
		this->isDone = true;
}

CDestroyEffect::CDestroyEffect()
{

}
CDestroyEffect::CDestroyEffect(float x, float y,int type)
{
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	if (type == 1)
	{
		this->EffectSprite = new CAnimation(200);
		EffectSprite->Add(EFFECT, 0);
		EffectSprite->Add(EFFECT, 1);
		EffectSprite->Add(EFFECT, 2);
	}
	else
	{
		this->EffectSprite = new CAnimation(300);
		EffectSprite->Add(EFFECT, 3);
	}

}
void CDestroyEffect::Render()
{
	this->EffectSprite->Render(x, y, default_color);

}