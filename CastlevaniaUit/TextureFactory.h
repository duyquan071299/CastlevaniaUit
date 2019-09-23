#pragma once
#include"Textures.h"

class CTextureFactory
{
private:
	static CTextureFactory * instance;

	unordered_map<GraphicType, LPDIRECT3DTEXTURE9> textures;
public:
	void LoadTextures();
	static CTextureFactory * GetInstance();
	void AddTextures(GraphicType type, const char* filePath, D3DCOLOR transparentColor);
	LPDIRECT3DTEXTURE9 GetTexture(GraphicType type);

};