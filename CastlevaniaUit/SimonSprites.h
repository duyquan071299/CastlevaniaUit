#pragma once
#include"Sprites.h"

class CSimonSprites : public CSprite
{
public:
	CSimonSprites() {};
	CSimonSprites(SimonState state,  int framenum, int columns)
	{
		type = PLAYER;
		texture = CTextureDatabase::GetInstance()->GetTexture(PLAYER);
		Framenum = framenum;
	
		Columns = columns;
		
	}
};