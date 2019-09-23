#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <dinput.h>
#include <WinUser.h>
#include <unordered_map>


using namespace std;
// Program values
#define WINDOW_CLASS_NAME "CastleVaniaUIT"
#define MAIN_WINDOW_TITLE "CastleVaniaUIT"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 0,255 )
#define MAX_FRAME_RATE 120
#define KEYBOARD_BUFFER_SIZE 1024


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
	MOVING,
	STANDING,
	RUNNING,
	JUMPING,
	FALLING,
	SITTING,
	ATTACKING,
	ATTACKING_STAND,
	ATTACKING_SIT,
	THROWING,
	CLINGING,
	CLIMBING,
	FLYING,
	ACTIVE,
	DEAD,
	INJURED
};

