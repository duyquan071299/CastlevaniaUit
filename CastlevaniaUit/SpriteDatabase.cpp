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
	sprites->AddSprite(new CSimonSprites(ATTACKING_SIT_LEFT, 15, 8));
	sprites->AddSprite(new CSimonSprites(ATTACKING_SIT_LEFT, 16, 8));
	sprites->AddSprite(new CSimonSprites(ATTACKING_SIT_LEFT, 17, 8));

	//Simon state right
	sprites->AddSprite(new CSimonSprites(STANDING_RIGHT, 31, 8));
	sprites->AddSprite(new CSimonSprites(WALKING_RIGHT, 30, 8));
	sprites->AddSprite(new CSimonSprites(WALKING_RIGHT, 29, 8));
	sprites->AddSprite(new CSimonSprites(WALKING_RIGHT, 28, 8));
	sprites->AddSprite(new CSimonSprites(SITTING_RIGHT, 27, 8));
	sprites->AddSprite(new CSimonSprites(ATTACKING_STAND_RIGHT, 26, 8));
	sprites->AddSprite(new CSimonSprites(ATTACKING_STAND_RIGHT, 25, 8));
	sprites->AddSprite(new CSimonSprites(ATTACKING_STAND_RIGHT, 24, 8));
	sprites->AddSprite(new CSimonSprites(ATTACKING_SIT_RIGHT, 32, 8));
	sprites->AddSprite(new CSimonSprites(ATTACKING_SIT_RIGHT, 47, 8));
	sprites->AddSprite(new CSimonSprites(ATTACKING_SIT_RIGHT, 46, 8));
	
	//Weapon whip left
	sprites->AddSprite(new CWeaponSprite(WHIP_1_LEFT, 0, 4));
	sprites->AddSprite(new CWeaponSprite(WHIP_1_LEFT, 1, 4));
	sprites->AddSprite(new CWeaponSprite(WHIP_1_LEFT, 2, 4));
	sprites->AddSprite(new CWeaponSprite(WHIP_1_LEFT, 3, 4));
	sprites->AddSprite(new CWeaponSprite(WHIP_2_LEFT, 4, 4));
	sprites->AddSprite(new CWeaponSprite(WHIP_2_LEFT, 5, 4));
	sprites->AddSprite(new CWeaponSprite(WHIP_2_LEFT, 6, 4));
	sprites->AddSprite(new CWeaponSprite(WHIP_3_LEFT, 8, 4));
	sprites->AddSprite(new CWeaponSprite(WHIP_3_LEFT, 9, 4));
	sprites->AddSprite(new CWeaponSprite(WHIP_3_LEFT, 10, 4));
	//Weapon whip right
	sprites->AddSprite(new CWeaponSprite(WHIP_1_RIGHT, 15, 4));
	sprites->AddSprite(new CWeaponSprite(WHIP_1_RIGHT, 14, 4));
	sprites->AddSprite(new CWeaponSprite(WHIP_1_RIGHT, 13, 4));
	sprites->AddSprite(new CWeaponSprite(WHIP_2_RIGHT, 19, 4));
	sprites->AddSprite(new CWeaponSprite(WHIP_2_RIGHT, 18, 4));
	sprites->AddSprite(new CWeaponSprite(WHIP_2_RIGHT, 17, 4));
	sprites->AddSprite(new CWeaponSprite(WHIP_3_RIGHT, 23, 4));
	sprites->AddSprite(new CWeaponSprite(WHIP_3_RIGHT,22, 4));
	sprites->AddSprite(new CWeaponSprite(WHIP_3_RIGHT, 21, 4));

	//Large Candle
	sprites->AddSprite(new CCandleSprite(LARGE_CANDLE, 0, 3));
	sprites->AddSprite(new CCandleSprite(LARGE_CANDLE, 1, 3));



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