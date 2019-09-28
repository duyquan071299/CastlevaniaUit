#include"TextureDatabase.h"


CTextureDatabase * CTextureDatabase::instance = NULL;

void CTextureDatabase::AddTextures(GraphicType type, const char* filePath, D3DCOLOR transparentColor) {
	textures[type] = (new CTextures(filePath, transparentColor))->GetTexture();
}


void  CTextureDatabase::LoadTextures() {
	CTextureDatabase* textures = CTextureDatabase::GetInstance();
	textures->AddTextures(PLAYER, "Textures\\Simon.png", D3DCOLOR_XRGB(255, 255, 255));

}

LPDIRECT3DTEXTURE9 CTextureDatabase::GetTexture(GraphicType type) {
	switch (type)
	{
	case HOLDER: case ITEM: case WEAPON:
		return textures[ITEM];
	case ENEMY:
		return textures[ENEMY];
	default:
		return textures[type];
	}
}



CTextureDatabase *CTextureDatabase::GetInstance() {
	if (instance == NULL) instance = new CTextureDatabase();
	return instance;
}