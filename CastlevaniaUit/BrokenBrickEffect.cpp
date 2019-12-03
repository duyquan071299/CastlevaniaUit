#include"BrokenBrickEffect.h"



void CBrokenBrickEffect::Update(DWORD dt)
{
	this->x += vx * dt;
	this->y += vy * dt;
	vy += 0.0015f*dt;
	if (this->EffectSprite->IsLastFrame() == true)
		this->isDone = true;
}

CBrokenBrickEffect::CBrokenBrickEffect()
{

}
CBrokenBrickEffect::CBrokenBrickEffect(float x, float y, float vx, float vy)
{
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	this->EffectSprite = new CAnimation(300);
	this->EffectSprite->Add(EFFECT, 4,1000);
	
}
void CBrokenBrickEffect::Render()
{
	this->EffectSprite->Render(x, y, default_color);

}