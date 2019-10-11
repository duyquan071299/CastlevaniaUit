#pragma once
#include"Sprites.h"

class CWeaponSprite : public CSprite
{
public:
	CWeaponSprite() {};
	CWeaponSprite(ItemType item, int framenum, int columns)
	{
		type = WEAPON;
		texture = CTextureDatabase::GetInstance()->GetTexture(WEAPON);
		Framenum = framenum;
		Columns = columns;
		this->SetFrameWH(160, 68);

	}
};