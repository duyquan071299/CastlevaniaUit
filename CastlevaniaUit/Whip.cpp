#include"Whip.h"

CWhip::CWhip()
{
	LPANIMATION ani = new CAnimation(100);
	ani->Add(WEAPON, 3,10);
	ani->Add(WEAPON, 0);
	ani->Add(WEAPON, 1);
	ani->Add(WEAPON, 2);
	animations[WHIP_1_LEFT] = ani;

	ani = new CAnimation(100);
	ani->Add(WEAPON, 3, 10);
	ani->Add(WEAPON,10);
	ani->Add(WEAPON,11);
	ani->Add(WEAPON, 12);
	animations[WHIP_1_RIGHT] = ani;


	animation = animations[WHIP_1_RIGHT];
	x = 100;
}
void CWhip::Update(DWORD dt)
{

}
void CWhip::Render()
{
	animation->Render(x,y);
}

void CWhip::ChangeWeaponState(ItemType type)
{
	animation = animations[type];
}