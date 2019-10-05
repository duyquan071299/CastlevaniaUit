﻿#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <dinput.h>
#include <WinUser.h>
#include <unordered_map>


using namespace std;
// Program values
#define WINDOW_CLASS_NAME "CastleVaniaUIT"
#define MAIN_WINDOW_TITLE "CastleVaniaUIT"
#define SCREEN_WIDTH 1536
#define SCREEN_HEIGHT 365
#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0,0 )
#define MAX_FRAME_RATE 120
#define KEYBOARD_BUFFER_SIZE 1024
#define SIMON_RUNNING_SPEED 0.095f
#define CAM_X 0.0f
#define CAM_Y 0.0f




//directx
extern HINSTANCE hInstance;										// hInstance của windows hiện tại
extern HWND hWnd;												// hWnd hiện tại
extern LPD3DXSPRITE spriteHandler;								// SpriteHanlder hiện tại
extern LPDIRECT3DDEVICE9 d3ddv;								// Device directX hiện tại (nhằm đại diện card màn hình)
extern LPDIRECT3DSURFACE9 backBuffer;


//enum for sprite
extern enum GraphicType
{
	PLAYER,
	ITEM,
	WEAPON,
	GROUND,
	MAP,
	FONT,
	ENEMY,
	HOLDER,
	INTROSCENE,
};


extern enum SimonState
{
	WALKING,
	WALKING_LEFT,
	WALKING_RIGHT,
	STANDING,
	STANDING_LEFT,
	STANDING_RIGHT,
	JUMPING,
	FALLING,
	SITTING,
	SITTING_RIGHT,
	SITTING_LEFT,
	ATTACKING,
	ATTACKING_STAND,
	ATTACKING_STAND_LEFT,
	ATTACKING_STAND_RIGHT,
	ATTACKING_SIT_LEFT,
	ATTACKING_SIT_RIGHT,
	ACTIVE,
	DEAD,
	INJURED
};

