#pragma once
#include"GlobalObject.h"
#include"TextureDatabase.h"

class CSprite
{
protected:
	GraphicType type;
	int framenum;
	int framew = 60;
	int frameh = 66;
	int columns;

	LPDIRECT3DTEXTURE9 texture;
public:
	CSprite() {};
	CSprite(GraphicType type, int framenum, int columns, LPDIRECT3DTEXTURE9 tex);

	void Draw(float x, float y, int alpha = 255);

	GraphicType getType()
	{
		return type;
	}
};
typedef CSprite * LPSPRITE;