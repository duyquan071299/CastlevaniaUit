#pragma once
#include"GlobalObject.h"

class CSprite
{
	SpriteType type;
	int framenum;
	int framew = 60;
	int frameh = 66;
	int columns;

	LPDIRECT3DTEXTURE9 texture;
public:
	CSprite(SpriteType type, int framenum, int columns, LPDIRECT3DTEXTURE9 tex);

	void Draw(float x, float y, int alpha = 255);
};