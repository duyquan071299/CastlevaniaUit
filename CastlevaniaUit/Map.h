#pragma once
#include <fstream>
#include <sstream>
#include <d3dx9.h>
#include <string.h>
#include "Sprites.h"
#include"Camera.h"
#include"Brick.h"
#include"Candle.h"
#include"Textures.h"
#include"InvisibleObject.h"
#define TILE_WIDTH 32
#define TILE_HEIGHT 32

class CMap
{
private:
	int ** Matrix; // map data
	int Columns, Rows; // cols and rows of our map
	int ColStart, ColEnd;
	int TileWidth, TileHeight;
	int MapWidth, MapHeight;
	int MapCol;

	LPSPRITE TileSet;
	LPDIRECT3DTEXTURE9 TileTexture;





	void LoadMatrixBackground(LPCSTR fileMatrixMap);

	//vector<LPGAMEOBJECT> LoadMapObject(LPCSTR fileStaticObject);
	//vector<EnemySpawner *> LoadEnemySpawner(LPCSTR fileEnemies);
	
public:
	void DrawTileBackground();
	RECT rect;
	vector<LPGAMEOBJECT> WallObject;
	CMap(LPCSTR fileMatrixMap, LPCSTR fileTileSet);
	LPDIRECT3DTEXTURE9 GetTileTexture() { return TileTexture; }
	int GetMapCol() { return MapCol; }
	~CMap();



	int** GetMapMat()
	{
		return Matrix;
	}
	void Draw();
	void SetMapWidth(int MapWidth) { this->MapWidth = MapWidth; }
	int GetMapWidth() { return this->MapWidth; }
	int GetMapHeight() { return this->MapHeight; }
	bool isContain(RECT rect1, RECT rect2);

	void Update(DWORD dt);
};
typedef CMap * LPMAP;
