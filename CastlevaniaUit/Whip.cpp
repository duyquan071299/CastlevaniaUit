#include"Whip.h"
#define WHIP_1_WIDTH 50
#define WHIP_2_WIDTH 50
#define WHIP_3_WIDTH 80
#define WHIP_HEIGHT 16
#define WHIP_BBOX_POS_X_RIGHT 80
#define WHIP_BBOX_POS_X_LEFT 30
#define WHIP_3_BBOX_POS_X 0
#define WHIP_BBOX_POS_Y 16

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

	animation = animations[WHIP_1_RIGHT];
	
}
void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (animation->GetCurrentFrame() == 3)
	{
		for (UINT i = 0; i < coObjects->size(); i++)
		{

			if (isContain(GetBBox(), coObjects->at(i)->GetBBox()))
			{
				if (dynamic_cast<CCandle *>(coObjects->at(i)))
				{
					dynamic_cast<CCandle *>(coObjects->at(i))->ChangeAnimation();
				}
				else if (dynamic_cast<CEnemy*>(coObjects->at(i)))
				{
					dynamic_cast<CEnemy*>(coObjects->at(i))->ChangeAnimation();
				}
			}
		}
	}

}
void CWhip::Render()
{
	animation->Render(x,y, default_color);
	RenderBoundingBox();
}
void CWhip::ChangeWeaponState(int nx)
{
	if (nx > 0)
	{
		if (WhipType == 1)
		{
			animation = animations[WHIP_1_RIGHT];
			WhipWidth = WHIP_1_WIDTH;
		}
		else if (WhipType == 2)
		{
			animation = animations[WHIP_2_RIGHT];
			WhipWidth = WHIP_2_WIDTH;

		}
		else
		{
			animation = animations[WHIP_3_RIGHT];
			WhipWidth = WHIP_3_WIDTH;
		}
	}
	else
	{
		if (WhipType == 1)
		{
			animation = animations[WHIP_1_LEFT];
			WhipWidth = WHIP_1_WIDTH;
		}
		else if (WhipType == 2)
		{
			animation = animations[WHIP_2_LEFT];
			WhipWidth = WHIP_2_WIDTH;

		}
		else
		{
			animation = animations[WHIP_3_LEFT];
			WhipWidth = WHIP_3_WIDTH;
		}
	}
	
}
void CWhip::GetBoundingBox(float &x, float &y, float &framew, float &frameh)
{
	framew = WhipWidth;
	frameh = WHIP_HEIGHT;
	y = this->y + WHIP_BBOX_POS_Y;
	if (nx >= 0)
		x = this->x + WHIP_BBOX_POS_X_RIGHT;
	else
	{
		if (WhipType == 3)
			x = this->x + WHIP_3_BBOX_POS_X;
		else
			x = this->x + WHIP_BBOX_POS_X_LEFT;
	}

}