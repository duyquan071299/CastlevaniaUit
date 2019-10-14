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

	ani = new CAnimation(100);
	ani->Add(WEAPON, 3, 10);
	ani->Add(WEAPON, 4);
	ani->Add(WEAPON, 5);
	ani->Add(WEAPON, 6);
	animations[WHIP_2_LEFT] = ani;
	ani = new CAnimation(100);
	ani->Add(WEAPON, 3, 10);
	ani->Add(WEAPON, 13);
	ani->Add(WEAPON, 14);
	ani->Add(WEAPON, 15);
	animations[WHIP_2_RIGHT] = ani;

	ani = new CAnimation(100);
	ani->Add(WEAPON, 3, 10);
	ani->Add(WEAPON, 7);
	ani->Add(WEAPON, 8);
	ani->Add(WEAPON, 9);
	animations[WHIP_3_LEFT] = ani;
	ani = new CAnimation(100);
	ani->Add(WEAPON, 3, 10);
	ani->Add(WEAPON, 16);
	ani->Add(WEAPON, 17);
	ani->Add(WEAPON, 18);
	animations[WHIP_3_RIGHT] = ani;





	animation = animations[WHIP_2_RIGHT];
	x = 100;
}
void CWhip::Update(DWORD dt)
{

}
void CWhip::Render()
{
	animation->Render(x,y);
}

void CWhip::ChangeWeaponState(int nx)
{
	if (nx > 0)
	{
		if (WhipType == 1)
		{
			animation = animations[WHIP_1_RIGHT];
		}
		else if (WhipType == 2)
		{
			animation = animations[WHIP_2_RIGHT];
		}
		else
		{
			animation = animations[WHIP_3_RIGHT];
		}
	}
	else
	{
		if (WhipType == 1)
		{
			animation = animations[WHIP_1_LEFT];
		}
		else if (WhipType == 2)
		{
			animation = animations[WHIP_2_LEFT];
		}
		else
		{
			animation = animations[WHIP_3_LEFT];
		}
	}
	
}