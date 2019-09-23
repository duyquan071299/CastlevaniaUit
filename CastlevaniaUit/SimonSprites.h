#pragma once
#include"Sprites.h"

class CSimonSprites : public CSprite
{
public:
	CSimonSprites() {};
	CSimonSprites(SimonState state,  int framenum, int columns)
	{
		type = PLAYER;
		texture = CTextureFactory::GetInstance()->GetTexture(PLAYER);
		framenum = framenum;
		columns = columns;
		
	}
};