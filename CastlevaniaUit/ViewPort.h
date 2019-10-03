#pragma once
#include <d3dx9.h>

class CViewPort
{
private:
	static CViewPort *instance;
	D3DXVECTOR3 cameraPos;

	int cameraWidth, cameraHeight;

	RECT region;
public:
	CViewPort();
	~CViewPort();
	static CViewPort * GetInstance();
	D3DXVECTOR3 ConvertPosInViewPort(D3DXVECTOR3 realPos);

	void SetCameraPos(D3DXVECTOR3 _camPos);

	void SetCameraSize(int width, int height) { cameraWidth = width; cameraHeight = height; }

	int GetCameraWidth() { return cameraWidth; }
	int GetCameraHeight() { return cameraHeight; }

	D3DXVECTOR3 GetCameraPos() { return this->cameraPos; }

	RECT GetBoundingBox();
};

