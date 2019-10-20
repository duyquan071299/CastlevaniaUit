#pragma once
#include"Sprites.h"

class CItemSprite : public CSprite
{
public:
	CItemSprite() {};
	CItemSprite(ItemType item, int framenum, int columns, int framew, int frameh)
	{
		type = ITEM;
		texture = CTextureDatabase::GetInstance()->GetTexture(ITEM);
		Framenum = framenum;
		Columns = columns;
		this->SetFrameWH(framew, frameh);

	}
};