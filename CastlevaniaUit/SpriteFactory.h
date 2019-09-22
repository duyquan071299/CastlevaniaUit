#pragma once
#include "Sprites.h"

class CSpriteFactory
{
private:
	static CSpriteFactory* _instance;
	std::unordered_map<SpriteType, std::vector<CSprite*>> sprites;		// Các Sprite theo Tag của Object cho trước

public:
	void LoadResources();
	void AddSprite(CSprite* sprite);
	CSprite* GetSprite(SpriteType type);
	std::vector<CSprite*> GetSprites(SpriteType type, int firstIndex, int lastIndex);
	static CSpriteFactory* GetInstance();
};