#include"GlobalObject.h"


HINSTANCE hInstance = NULL;						// hInstance của windows hiện tại
HWND hWnd = NULL;								// hWnd hiện tại
LPD3DXSPRITE spriteHandler = NULL;			// SpriteHanlder hiện tại
LPDIRECT3DDEVICE9 d3ddv = NULL;		// Device directX hiện tại (nhằm đại diện card màn hình)
LPDIRECT3DSURFACE9 backBuffer = NULL;		// BackBuffer	
LPDIRECT3D9 d3d = NULL;						// Direct3D handle