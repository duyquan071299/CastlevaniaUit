#include"SpriteDatabase.h"


CSpriteDatabase * CSpriteDatabase::instance = NULL;

void CSpriteDatabase::LoadResources()
{
	CSpriteDatabase* sprites = CSpriteDatabase::GetInstance();
	sprites->AddSprite(new CSimonSprites(STANDING, 0,8 ));

}

void CSpriteDatabase::AddSprite(CSprite* sprite)
{
	sprites[sprite->getType()]=sprite;
}
LPSPRITE CSpriteDatabase::GetSprite(GraphicType type)
{
	return sprites[type];
}
/*CSprite* CSpriteDatabase::GetSprite(GraphicType type,int index) {
	return sprites[type][index];

}
LPSPRITE CSpriteDatabase::GetSprites(GraphicType type, int firstIndex, int lastIndex){
	auto first = sprites[type].begin() + firstIndex;
	auto last = sprites[type].begin() + lastIndex;
	return std::vector<CSprite*>(first, last + 1);
}
*/
CSpriteDatabase* CSpriteDatabase::GetInstance(){
	if (instance == NULL)
		instance = new CSpriteDatabase();
	return instance;
}