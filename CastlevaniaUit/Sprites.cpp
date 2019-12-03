#include"Sprites.h"

CSprite::CSprite(GraphicType type, int framenum, int columns)
{
	this->type = type;
	this->Framenum = framenum;
	this->Columns = columns;
}
CSprite::CSprite(GraphicType type, int framenum, int columns, int Framew, int Frameh)
{
	this->type = type;
	this->Framenum = framenum;
	this->Columns = columns;
	this->Framew = Framew;
	this->Frameh = Frameh;
}

void CSprite::Draw(float x, float y, D3DCOLOR color)
{

	D3DXVECTOR3 position(floor(x- CCamera::GetInstance()->x), floor(y- CCamera::GetInstance()->y), 0);
	RECT rect;
	rect.left = (Framenum % Columns) * Framew;
	rect.top = (Framenum / Columns) * Frameh;
	rect.right = rect.left + Framew;
	rect.bottom = rect.top + Frameh;
	spriteHandler->Draw(texture, &rect, NULL, &position, color);


	
}

void CSprite::DrawScoreBoard(float x, float y, D3DCOLOR color)
{

	D3DXVECTOR3 position(floor(x), floor(y ), 0);
	RECT rect;
	rect.left = (Framenum % Columns) * Framew;
	rect.top = (Framenum / Columns) * Frameh;
	rect.right = rect.left + Framew;
	rect.bottom = rect.top + Frameh;
	spriteHandler->Draw(texture, &rect, NULL, &position, color);
}
