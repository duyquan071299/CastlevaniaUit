﻿#include"GlobalObject.h"


HINSTANCE hInstance = NULL;						
HWND hWnd = NULL;							
LPD3DXSPRITE spriteHandler = NULL;			
LPDIRECT3DDEVICE9 d3ddv = NULL;		
LPDIRECT3DSURFACE9 backBuffer = NULL;		
LPDIRECT3D9 d3d = NULL;
D3DCOLOR default_color = D3DCOLOR_ARGB(255, 255, 255, 255);