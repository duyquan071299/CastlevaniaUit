#pragma once
#include"Textures.h"

class CTextureDatabase
{
private:
	static CTextureDatabase * instance;

	unordered_map<GraphicType, LPDIRECT3DTEXTURE9> textures;
public:
	void LoadTextures();
	static CTextureDatabase * GetInstance();
	void AddTextures(GraphicType type, const char* filePath, D3DCOLOR transparentColor);
	LPDIRECT3DTEXTURE9 GetTexture(GraphicType type);

};