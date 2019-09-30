#include"Sprites.h"

CSprite::CSprite(GraphicType type, int framenum, int columns)
{
	this->type = type;
	this->Framenum = framenum;
	this->Columns = columns;
}


void CSprite::Draw(float x, float y, int alpha)
{
	D3DXVECTOR3 position(x + CAM_X, y + CAM_Y, 0);
	D3DXVECTOR3 center(Framew / 2, Frameh / 2, 0);
	RECT rect;
	rect.left = (Framenum % Columns) * Framew;
	rect.top = (Framenum / Columns) * Frameh;
	rect.right = rect.left + Framew;
	rect.bottom = rect.top + Frameh;
	spriteHandler->Draw(texture, &rect, &center, &position, D3DCOLOR_ARGB(alpha, 255, 255, 255));
}

