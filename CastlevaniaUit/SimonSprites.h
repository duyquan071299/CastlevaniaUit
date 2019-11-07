#pragma once
#include"Sprites.h"

class CSimonSprites : public CSprite
{
public:
	CSimonSprites() {};
	CSimonSprites(State state,  int framenum, int columns,int framew,int frameh)
	{
		type = PLAYER;
		texture = CTextureDatabase::GetInstance()->GetTexture(PLAYER);
		Framenum = framenum;
		Columns = columns;
		SetFrameWH(framew, frameh);
		
	}
};