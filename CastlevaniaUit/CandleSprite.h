#pragma once
#include"Sprites.h"


class CCandleSprite : public CSprite
{
public:
	CCandleSprite() {};
	CCandleSprite(ItemType item, int framenum, int columns)
	{
		type = CANDLE;
		texture = CTextureDatabase::GetInstance()->GetTexture(CANDLE);
		Framenum = framenum;
		Columns = columns;
		this->SetFrameWH(32, 64);

	}
};