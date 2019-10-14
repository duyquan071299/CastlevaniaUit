#pragma once
#include "Sprites.h"
#include"SimonSprites.h"
#include"WeaponSprite.h"
#include"CandleSprite.h"
class CSpriteDatabase
{
private:
	static CSpriteDatabase* instance;
	unordered_map<GraphicType, vector<LPSPRITE>> sprites;		// Các Sprite theo Tag của Object cho trước

public:
	void LoadResources();
	void AddSprite(LPSPRITE sprite);
	LPSPRITE GetSprite(GraphicType type,int index);
	//LPSPRITE GetSprites(GraphicType type, int firstIndex, int lastIndex);
	//LPSPRITE GetSprite(GraphicType type);
	//LPSPRITE &operator[](GraphicType type) { return sprites[type]; }
	static CSpriteDatabase* GetInstance();
};