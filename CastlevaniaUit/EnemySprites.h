#pragma once
#include"Sprites.h"

class CEnemySprites : public CSprite
{
public:
	CEnemySprites() {};
	CEnemySprites(EnemyType enemytype, int framenum, int columns, int framew, int frameh)
	{
		type = ENEMY;
		texture = CTextureDatabase::GetInstance()->GetTexture(ENEMY);
		Framenum = framenum;
		Columns = columns;
		SetFrameWH(framew, frameh);

	}
};