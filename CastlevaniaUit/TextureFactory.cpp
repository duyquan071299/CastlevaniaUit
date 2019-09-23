#include"TextureFactory.h"


CTextureFactory * CTextureFactory::instance = NULL;

void CTextureFactory::AddTextures(GraphicType type, const char* filePath, D3DCOLOR transparentColor) {
	textures[type] = (new CTextures(filePath, transparentColor))->GetTexture();
}


void  CTextureFactory::LoadTextures() {
	CTextureFactory* textures = CTextureFactory::GetInstance();
	textures->AddTextures(PLAYER, "Textures\\Simon.png", D3DCOLOR_XRGB(255, 255, 255));

}

LPDIRECT3DTEXTURE9 CTextureFactory::GetTexture(GraphicType type) {
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



CTextureFactory *CTextureFactory::GetInstance() {
	if (instance == NULL) instance = new CTextureFactory();
	return instance;
}