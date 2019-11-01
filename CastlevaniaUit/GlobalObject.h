﻿#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <dinput.h>
#include <WinUser.h>
#include <unordered_map>
#include <fstream>
#include<string>
#include<cmath>


using namespace std;
// Program values
#define WINDOW_CLASS_NAME "CastleVaniaUIT"
#define MAIN_WINDOW_TITLE "CastleVaniaUIT"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0,0 )
#define MAX_FRAME_RATE 120
#define KEYBOARD_BUFFER_SIZE 1024
#define SIMON_RUNNING_SPEED 0.1f
#define SIMON_JUMPING_SPEED 0.53f
#define DAGGER_SPEED 0.025f
#define COLLECT_ITEM_TIME 500
#define LANDING_TIME 300
#define ITEM_LIFE_TIME 3000
#define CAM_X 0.0f
#define CAM_Y 0.0f
#define GAME_GRAVITY 0.002f
#define PI 3.14159
#define FREQUENCY 50
#define AMP 100




//directx
extern HINSTANCE hInstance;										// hInstance của windows hiện tại
extern HWND hWnd;												// hWnd hiện tại
extern LPD3DXSPRITE spriteHandler;								// SpriteHanlder hiện tại
extern LPDIRECT3DDEVICE9 d3ddv;								// Device directX hiện tại (nhằm đại diện card màn hình)
extern LPDIRECT3DSURFACE9 backBuffer;
extern D3DCOLOR default_color;



//enum for sprite
enum GraphicType
{
	PLAYER,
	ITEM,
	WEAPON,
	GROUND,
	BOSS,
	FONT,
	ENEMY,
	BBOX,
	CANDLE,
	INTROSCENE,
	EFFECT,
	PANTHER,
	MAP,
	
};	


enum SimonState
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
	ONSTAIR_UP_LEFT,
	ONSTAIR_STANDING_LEFT,
	ONSTAIR_DOWN_LEFT,
	ONSTAIR_UP_ATTACK_LEFT,
	ONSTAIR_DOWN_ATTACK_LEFT,
	ONSTAIR_UP_RIGHT,
	ONSTAIR_STANDING_RIGHT,
	ONSTAIR_DOWN_RIGHT,
	ONSTAIR_UP_ATTACK_RIGHT,
	ONSTAIR_DOWN_ATTACK_RIGHT,
	ACTIVE,
	DEAD,
	INJURED
};

enum ItemType
{
	WHIP_1_RIGHT,
	WHIP_2_RIGHT,
	WHIP_3_RIGHT,
	WHIP_1_LEFT,
	WHIP_2_LEFT,
	WHIP_3_LEFT,
	SMALL_CANDLE,
	LARGE_CANDLE,
	BRICK,
	HOLDER,
	DAGGER_LEFT,
	DAGGER_RIGHT,


};

enum HolderType
{
	HEART,
	LARGE_HEART,
	MONEY_1,
	MONEY_2,
	MONEY_3,
	WHIP,
	DAGGER,
	WATCH,
	CROSS,
	AXE,
	POTION,
	CHEST_1,
	CHEST_2,
	HOLYWATER,
	CHICKEN,
};

enum EffectType
{
	FIRE,
	DESTROYED,
};