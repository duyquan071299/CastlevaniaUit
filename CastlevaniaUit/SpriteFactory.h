#pragma once
#include "Sprites.h"
#include"SimonSprites.h"
class CSpriteFactory
{
private:
	static CSpriteFactory* instance;
	unordered_map<GraphicType, std::vector<CSprite*>> sprites;		// Các Sprite theo Tag của Object cho trước

public:
	void LoadResources();
	void AddSprite(CSprite* sprite);
	CSprite* GetSprite(GraphicType type,int index);
	std::vector<CSprite*> GetSprites(GraphicType type, int firstIndex, int lastIndex);
	static CSpriteFactory* GetInstance();
};