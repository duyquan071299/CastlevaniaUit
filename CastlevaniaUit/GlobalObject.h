﻿#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <dinput.h>
#include <WinUser.h>
#include <unordered_map>
#include <fstream>
#include<string>
#include<cmath>
#include <unordered_set>

using namespace std;
// Program values
#define WINDOW_CLASS_NAME "CastleVaniaUIT"
#define MAIN_WINDOW_TITLE "CastleVaniaUIT"
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 475
#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0,0 )
#define BACKGROUND_COLOR_2 D3DCOLOR_XRGB(255, 255,255 )
#define MAX_FRAME_RATE 120
#define KEYBOARD_BUFFER_SIZE 1024
#define SIMON_RUNNING_SPEED 0.18f
#define SIMON_JUMPING_SPEED 0.5f
#define SIMON_ONSTAIR_SPEED 0.07f
#define DAGGER_SPEED 0.35f
#define HOLY_WATER_SPEED_X 0.2f
#define HOLY_WATER_SPEED_Y 0.002f
#define COLLECT_ITEM_TIME 500
#define UNTOUCHABLE_TIME 3000
#define LANDING_TIME 300
#define ITEM_LIFE_TIME 3000
#define FROZEN_TIME 3000
#define CROSS_TIME 1000
#define GHOST_RESPAWN_TIME 1000
#define BAT_RESPAWN_TIME 1500
#define ENEMY_BULLET_SPEED 0.015
#define CAM_X 0.0f
#define CAM_Y 0.0f
#define GAME_GRAVITY 0.002f
#define RESPAWN_POSITION_Y 335
#define GHOST_RESPAWN_REGION_1_LEFT -10.0f
#define GHOST_RESPAWN_REGION_1_RIGHT 832.0f
#define GHOST_RESPAWN_REGION_2_LEFT 2304.0f
#define GHOST_RESPAWN_REGION_2_RIGHT 3056.0f
#define BAT_RESPAWN_REGION_LEFT 3046.0f
#define BAT_RESPAWN_REGION_RIGHT 4086.0f
#define KAPPA_RESPAWN_REGION_1_LEFT 3046.0f
#define KAPPA_RESPAWN_REGION_1_RIGHT 4160.0f
#define KAPPA_RESPAWN_Y 808.0f
#define KAPPA_RESPAWN_X_1 3200.0f
#define KAPPA_RESPAWN_X_2 3328.0f
#define KAPPA_RESPAWN_X_3 3430.0f
#define KAPPA_RESPAWN_X_4 3580.0f
#define KAPPA_RESPAWN_X_5 3700.0f
#define KAPPA_RESPAWN_X_6 3836.0f
#define KAPPA_RESPAWN_X_7 3932.0f
#define KAPPA_RESPAWN_ZONE_1 3110.0f
#define KAPPA_RESPAWN_ZONE_2 3264.0f
#define KAPPA_RESPAWN_ZONE_3 3379.0f
#define KAPPA_RESPAWN_ZONE_4 3505.0f
#define KAPPA_RESPAWN_ZONE_5 3640.0f
#define KAPPA_RESPAWN_ZONE_6 3768.0f
#define KAPPA_RESPAWN_ZONE_7 3884.0f
#define KAPPA_RESPAWN_ZONE_8 4022.0f
#define PANTHER_RESPAWN_X_1 1380.0f
#define PANTHER_RESPAWN_X_2 1760.0f
#define PANTHER_RESPAWN_X_3 1888.0f
#define PANTHER_RESPAWN_Y_1 158.0f
#define PANTHER_RESPAWN_Y_2 50.0f
#define PANTHER_RUNNING_X_LEFT_1 1216.0f
#define PANTHER_RUNNING_X_LEFT_2 1568.0f
#define PANTHER_RUNNING_X_LEFT_3 1792.0f
#define PANTHER_RUNNING_X_RIGHT_1 1504.0f
#define PANTHER_RUNNING_X_RIGHT_2 1824.0f
#define PANTHER_RUNNING_X_RIGHT_3 1984.0f
#define PANTHER_RESPAWN_ZONE_X_LEFT_1 884.0f
#define PANTHER_RESPAWN_ZONE_X_LEFT_2 1264.0f
#define PANTHER_RESPAWN_ZONE_X_LEFT_3 1392.0f
#define PANTHER_RESPAWN_ZONE_X_RIGHT_1 1876.0f
#define PANTHER_RESPAWN_ZONE_X_RIGHT_2 2256.0f
#define PANTHER_RESPAWN_ZONE_X_RIGHT_3 2384.0f


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
	DOOR,
	BOSS,
	FONT,
	ENEMY,
	BBOX,
	CANDLE,
	INTROSCENE,
	EFFECT,
	MAP,
	HIDING_OBJECT,
	SCORE_BOARD,
	HEAL,
	
};	


enum State
{
	WALKING_LEFT,
	WALKING_RIGHT,
	STANDING_LEFT,
	STANDING_RIGHT,
	JUMPING_LEFT,
	JUMPING_RIGHT,
	SITTING_RIGHT,
	SITTING_LEFT,
	ATTACKING_STAND_LEFT,
	ATTACKING_STAND_RIGHT,
	ATTACKING_SIT_LEFT,
	ATTACKING_SIT_RIGHT,
	ONSTAIR_WALKING_DOWN_LEFT,
	ONSTAIR_WALKING_UP_LEFT,
	ONSTAIR_STANDING_UP_LEFT,
	ONSTAIR_STANDING_DOWN_LEFT,
	ONSTAIR_DOWN_ATTACK_LEFT,
	ONSTAIR_UP_ATTACK_LEFT,
	ONSTAIR_WALKING_DOWN_RIGHT,
	ONSTAIR_WALKING_UP_RIGHT,
	ONSTAIR_STANDING_UP_RIGHT,
	ONSTAIR_STANDING_DOWN_RIGHT,
	ONSTAIR_DOWN_ATTACK_RIGHT,
	ONSTAIR_UP_ATTACK_RIGHT,
	INJURED_LEFT,
	INJURED_RIGHT,
	ACTIVE,
	DEAD,
	OPEN,
	CLOSE,
	OPENNING,
	CLOSING,
	NORMAL_LEFT,
	NORMAL_RIGHT,
	BURN_LEFT,
	BURN_RIGHT,
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
	HOLYWATER_LEFT,
	HOLYWATER_RIGHT,
	AXE_RIGHT,
	AXE_LEFT,


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
enum EnemyType 
{
	GHOST,
	KAPPA,
	PANTHER,
	BAT,
	
};

