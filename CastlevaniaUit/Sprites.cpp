#include"Sprites.h"

CSprite::CSprite(GraphicType type, int framenum, int columns, LPDIRECT3DTEXTURE9 tex)
{
	this->type = type;
	this->framenum = framenum;
	this->columns = columns;
	this->texture = tex;
}


void CSprite::Draw(float x, float y, int alpha)
{
	D3DXVECTOR3 position(x - CAM_X, y - CAM_Y, 0);
	D3DXVECTOR3 center(framew / 2, frameh / 2, 0);
	RECT rect;
	rect.left = (framenum % columns) * framew;
	rect.top = (framenum / columns) * frameh;
	rect.right = rect.left + framew;
	rect.bottom = rect.top + frameh;
	spriteHandler->Draw(texture, &rect, &center, &position, D3DCOLOR_ARGB(alpha, 255, 255, 255));
}