#include"Sprites.h"

CSprite::CSprite(SpriteType type, int framenum, int columns, LPDIRECT3DTEXTURE9 tex)
{
	this->type = type;
	this->framenum = framenum;
	this->columns = columns;
	this->texture = tex;
}


