#include"SpriteDatabase.h"


CSpriteDatabase * CSpriteDatabase::instance = NULL;

void CSpriteDatabase::LoadResources()
{
	CSpriteDatabase* sprites = CSpriteDatabase::GetInstance();
	//Simon state left
	sprites->AddSprite(new CSimonSprites(STANDING_LEFT, 0,8 ));
	sprites->AddSprite(new CSimonSprites(WALKING_LEFT, 1, 8));
	sprites->AddSprite(new CSimonSprites(WALKING_LEFT, 2, 8));
	sprites->AddSprite(new CSimonSprites(WALKING_LEFT, 3, 8));
	sprites->AddSprite(new CSimonSprites(SITTING_LEFT, 4, 8));
	sprites->AddSprite(new CSimonSprites(ATTACKING_STAND_LEFT, 5, 8));
	sprites->AddSprite(new CSimonSprites(ATTACKING_STAND_LEFT, 6, 8));
	sprites->AddSprite(new CSimonSprites(ATTACKING_STAND_LEFT, 7, 8));
	//Simon state right
	sprites->AddSprite(new CSimonSprites(STANDING_RIGHT, 31, 8));
	sprites->AddSprite(new CSimonSprites(WALKING_RIGHT, 30, 8));
	sprites->AddSprite(new CSimonSprites(WALKING_RIGHT, 29, 8));
	sprites->AddSprite(new CSimonSprites(WALKING_RIGHT, 28, 8));
	sprites->AddSprite(new CSimonSprites(SITTING_RIGHT, 27, 8));
	sprites->AddSprite(new CSimonSprites(ATTACKING_STAND_RIGHT, 26, 8));
	sprites->AddSprite(new CSimonSprites(ATTACKING_STAND_RIGHT, 25, 8));
	sprites->AddSprite(new CSimonSprites(ATTACKING_STAND_RIGHT, 24, 8));

}

void CSpriteDatabase::AddSprite(LPSPRITE sprite)
{
	sprites[sprite->getType()].push_back(sprite);

}

LPSPRITE CSpriteDatabase::GetSprite(GraphicType type,int index) {
	return sprites[type][index];

}
//LPSPRITE CSpriteDatabase::GetSprites(GraphicType type, int firstIndex, int lastIndex){
//	auto first = sprites[type].begin() + firstIndex;
//	auto last = sprites[type].begin() + lastIndex;
//	return std::vector<CSprite*>(first, last + 1);
//}

CSpriteDatabase* CSpriteDatabase::GetInstance(){
	if (instance == NULL)
		instance = new CSpriteDatabase();
	return instance;
}