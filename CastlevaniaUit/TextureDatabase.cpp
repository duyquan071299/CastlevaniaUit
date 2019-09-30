#include"TextureDatabase.h"


CTextureDatabase * CTextureDatabase::instance = NULL;

void CTextureDatabase::AddTextures(GraphicType type, const char* filePath, D3DCOLOR transparentColor) {
	textures[type] = (new CTextures(filePath, transparentColor))->GetTexture();
}


void  CTextureDatabase::LoadTextures() {
	CTextureDatabase* textures = CTextureDatabase::GetInstance();
	textures->AddTextures(PLAYER, "Resources\\Textures\\Simon.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->AddTextures(MAP, "Resources\\Maps\\Scene1_TileSet.png", D3DCOLOR_XRGB(0, 0, 0));

}

LPDIRECT3DTEXTURE9 CTextureDatabase::GetTexture(GraphicType type) {
	switch (type)
	{
	case HOLDER: case ITEM: case WEAPON:
		return textures[ITEM];
	case ENEMY:
		return textures[ENEMY];
	case MAP:
		return textures[MAP];
	default:
		return textures[type];
	}
}



CTextureDatabase *CTextureDatabase::GetInstance() {
	if (instance == NULL) 
		instance = new CTextureDatabase();
	return instance;
}