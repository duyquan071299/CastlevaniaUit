#pragma once
#include"Sprites.h"


class CDoorSprite : public CSprite
{
public:
	CDoorSprite() {};
	CDoorSprite(GraphicType Type, int framenum, int columns, int framew, int frameh)
	{
		type = Type;
		texture = CTextureDatabase::GetInstance()->GetTexture(DOOR);
		Framenum = framenum;
		Columns = columns;
		this->SetFrameWH(framew, frameh);

	}
};