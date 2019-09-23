#include"SpriteFactory.h"


CSpriteFactory * CSpriteFactory::instance = NULL;

void CSpriteFactory::LoadResources()
{
	CSpriteFactory* sprites = CSpriteFactory::GetInstance();
	sprites->AddSprite(new CSimonSprites(STANDING, 0,8 ));


}
void CSpriteFactory::AddSprite(CSprite* sprite)
{
	sprites[sprite->getType()].push_back(sprite);
}
CSprite* CSpriteFactory::GetSprite(GraphicType type,int index) {
	return sprites[type][index];

}
std::vector<CSprite*> CSpriteFactory::GetSprites(GraphicType type, int firstIndex, int lastIndex){
	auto first = sprites[type].begin() + firstIndex;
	auto last = sprites[type].begin() + lastIndex;
	return std::vector<CSprite*>(first, last + 1);
}

CSpriteFactory* CSpriteFactory::GetInstance(){
	if (instance == NULL)
		instance = new CSpriteFactory();
	return instance;
}