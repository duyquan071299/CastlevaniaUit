#pragma once
#include"Sprites.h"


class CEffectSprite : public CSprite
{
public:
	CEffectSprite() {};
	CEffectSprite(EffectType item, int framenum, int columns, int framew, int frameh)
	{
		type = EFFECT;
		texture = CTextureDatabase::GetInstance()->GetTexture(EFFECT);
		Framenum = framenum;
		Columns = columns;
		this->SetFrameWH(framew, frameh);

	}
};