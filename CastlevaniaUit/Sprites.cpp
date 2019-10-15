#include"Sprites.h"

CSprite::CSprite(GraphicType type, int framenum, int columns)
{
	this->type = type;
	this->Framenum = framenum;
	this->Columns = columns;
}


void CSprite::Draw(float x, float y, int alpha)
{
	
	D3DXVECTOR3 position(floor(x- CCamera::GetInstance()->x), floor(y- CCamera::GetInstance()->y), 0);
	RECT rect;
	rect.left = (Framenum % Columns) * Framew;
	rect.top = (Framenum / Columns) * Frameh;
	rect.right = rect.left + Framew;
	rect.bottom = rect.top + Frameh;
	spriteHandler->Draw(texture, &rect, NULL, &position, D3DCOLOR_ARGB(alpha, 255, 255, 255));
}

