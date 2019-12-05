#include"SpriteDatabase.h"


CSpriteDatabase * CSpriteDatabase::instance = NULL;

void CSpriteDatabase::LoadResources()
{
	CSpriteDatabase* sprites = CSpriteDatabase::GetInstance();
	string object;
	int number,type, frame, columns,framew,frameh;
	ifstream ifs("Resources\\Texts\\Sprite.txt");
	if (ifs.is_open()) {
		while (ifs.good()) {
			ifs >> object >> number;
			for (int i = 0; i < number; i++)
			{
				ifs >> type >> frame >> columns>>framew>>frameh;
				if (object == "s")
					sprites->AddSprite(new CSimonSprites(static_cast<State>(type), frame, columns, framew, frameh));
				else if (object == "w")
					sprites->AddSprite(new CWeaponSprite(static_cast<ItemType>(type), frame, columns,framew,frameh));
				else if (object == "lc")
					sprites->AddSprite(new CCandleSprite(static_cast<ItemType>(type), frame, columns, framew, frameh));
				else if(object=="hd")
					sprites->AddSprite(new CItemSprite(static_cast<ItemType>(type), frame, columns, framew, frameh));
				else if(object=="ef")
					sprites->AddSprite(new CEffectSprite(static_cast<EffectType>(type), frame, columns, framew, frameh));
				else if (object == "en")
					sprites->AddSprite(new CEnemySprites(static_cast<EnemyType>(type), frame, columns, framew, frameh));
				else if(object=="do")
					sprites->AddSprite(new CDoorSprite(static_cast<GraphicType>(type), frame, columns, framew, frameh));
				else 
					sprites->AddSprite(new CSprite(static_cast<GraphicType>(type), frame, columns, framew, frameh));
				/*else if(object=="sc")
					sprites->AddSprite(new CSprite(static_cast<GraphicType>(type),frame,columns, framew, frameh));
				else if (object == "fo")
					sprites->AddSprite(new CSprite(static_cast<GraphicType>(type), frame, columns, framew, frameh));
				else if (object == "he")
					sprites->AddSprite(new CSprite(static_cast<GraphicType>(type), frame, columns, framew, frameh));
				else if(object=="br")
					sprites->AddSprite(new CSprite(static_cast<GraphicType>(type), frame, columns, framew, frameh));
				else if(object=="it")
					sprites->AddSprite(new CSprite(static_cast<GraphicType>(type), frame, columns, framew, frameh));*/
			}
		}
	}

}

void CSpriteDatabase::AddSprite(LPSPRITE sprite)
{
	sprites[sprite->getType()].push_back(sprite);

}

LPSPRITE CSpriteDatabase::GetSprite(GraphicType type,int index) {
	if (sprites[type][index]->GetTexture() == NULL)
		sprites[type][index]->Settexture(CTextureDatabase::GetInstance()->GetTexture(type));
	return sprites[type][index];

}


CSpriteDatabase* CSpriteDatabase::GetInstance(){
	if (instance == NULL)
		instance = new CSpriteDatabase();
	return instance;
}