#pragma once
#include"GlobalObject.h"

class CTextures
{
private:
	LPDIRECT3DTEXTURE9 texture;
public:
	CTextures() {};
	CTextures(const char* filePath, D3DCOLOR transparentColor);
	
	LPDIRECT3DTEXTURE9 GetTexture();
	
};