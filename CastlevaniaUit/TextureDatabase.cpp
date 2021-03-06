#include"TextureDatabase.h"


CTextureDatabase * CTextureDatabase::instance = NULL;

void CTextureDatabase::AddTextures(GraphicType type, const char* filePath, D3DCOLOR transparentColor) {
	textures[type] = (new CTextures(filePath, transparentColor))->GetTexture();
}


void  CTextureDatabase::LoadTextures() {
	CTextureDatabase* textures = CTextureDatabase::GetInstance();
	int type;
	string filePath;
	const char* FilePath;
	ifstream ifs("Resources\\Texts\\Textures.txt");
	if (ifs.is_open()) {
		while (ifs.good()) {
			
			ifs >> type >> filePath;
			FilePath = filePath.c_str();
			textures->AddTextures(static_cast<GraphicType>(type), FilePath, D3DCOLOR_XRGB(255, 0, 255));

		}
	}
	
}

LPDIRECT3DTEXTURE9 CTextureDatabase::GetTexture(GraphicType type) {
	switch (type)
	{
	case ITEM:
		return textures[ITEM];
	default:
		return textures[type];
	}
	
}



CTextureDatabase *CTextureDatabase::GetInstance() {
	if (instance == NULL) 
		instance = new CTextureDatabase();
	return instance;
}