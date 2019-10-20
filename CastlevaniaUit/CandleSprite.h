#pragma once
#include"Sprites.h"


class CCandleSprite : public CSprite
{
public:
	CCandleSprite() {};
	CCandleSprite(ItemType item, int framenum, int columns,int framew, int frameh)
	{
		type = CANDLE;
		texture = CTextureDatabase::GetInstance()->GetTexture(CANDLE);
		Framenum = framenum;
		Columns = columns;
		this->SetFrameWH(framew, frameh);

	}
};