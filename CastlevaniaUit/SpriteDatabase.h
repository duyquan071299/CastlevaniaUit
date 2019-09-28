#pragma once
#include "Sprites.h"
#include"SimonSprites.h"
class CSpriteDatabase
{
private:
	static CSpriteDatabase* instance;
	unordered_map<GraphicType, LPSPRITE> sprites;		// Các Sprite theo Tag của Object cho trước

public:
	void LoadResources();
	void AddSprite(CSprite* sprite);
	//CSprite* GetSprite(GraphicType type,int index);
	//LPSPRITE GetSprites(GraphicType type, int firstIndex, int lastIndex);
	LPSPRITE GetSprite(GraphicType type);
	LPSPRITE &operator[](GraphicType type) { return sprites[type]; }
	static CSpriteDatabase* GetInstance();
};