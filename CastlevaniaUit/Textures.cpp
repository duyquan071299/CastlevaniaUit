#include"Textures.h"



CTextures::CTextures(const char* filePath, D3DCOLOR transparentColor){
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
	{
		OutputDebugString("[ERROR] GetImageInfoFromFile failed: %s\n");
		return;
	}
	LPDIRECT3DTEXTURE9 texture;

	result = D3DXCreateTextureFromFileEx(
		d3ddv,								// Pointer to Direct3D device object
		filePath,							// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transparentColor,
		&info,
		NULL,
		&texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		OutputDebugString("[ERROR] CreateTextureFromFile failed\n");
		return;
	}

}


LPDIRECT3DTEXTURE9 CTextures::GetTexture() {
	return texture;
}
