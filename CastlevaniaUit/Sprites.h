#pragma once
#include"GlobalObject.h"
#include"TextureDatabase.h"

class CSprite
{
protected:
	GraphicType type;
	int Framenum;
	int Framew = 60;
	int Frameh = 66;
	int Columns;
	LPDIRECT3DTEXTURE9 texture;
public:
	CSprite() {};
	CSprite(GraphicType type, int framenum, int columns);

	void Draw(float x, float y, int alpha = 255);

	GraphicType getType()
	{
		return type;
	}
	void SetFrameWH(int framew, int frameh)
	{
		this->Framew = framew;
		this->Frameh = frameh;
	}
	
	void Settexture(LPDIRECT3DTEXTURE9 texture)
	{
		this->texture = texture;
	}
};
typedef CSprite * LPSPRITE;