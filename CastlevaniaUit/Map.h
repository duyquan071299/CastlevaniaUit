#pragma once
#include <fstream>
#include <sstream>
#include <d3dx9.h>
#include <string.h>
#include "Sprites.h"
#include"Camera.h"
#include"LargeCandle.h"

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
	//int currentBackground;
	LPSPRITE TileSet;
	vector<LPSPRITE> listTileSet;
	vector<LPCSTR> listMapData;
	vector<LPGAMEOBJECT> listObject;



	void LoadMatrixBackground(LPCSTR fileMatrixMap);

	//vector<LPGAMEOBJECT> LoadMapObject(LPCSTR fileStaticObject);
	//vector<EnemySpawner *> LoadEnemySpawner(LPCSTR fileEnemies);
	
public:
	void DrawTileBackground();
	RECT rect;
	CMap(LPCSTR fileMatrixMap, LPCSTR fileTileSet, LPCSTR fileItemMap);

	~CMap();

	void AddTileSet(LPCSTR fileMatrixMap, LPCSTR fileTileSet);
	void DrawObject();
	vector<LPGAMEOBJECT> LoadMapObject(LPCSTR fileItemMap);

	//void SetCurrentBackground(int currentBackground);

	void Draw();

	int GetMapWidth() { return this->MapWidth; }
	int GetMapHeight() { return this->MapHeight; }
	bool isContain(RECT rect1, RECT rect2);
	//Grid * GetGrid() { return this->grid; }

	void Update(DWORD dt);
};
typedef CMap * LPMAP;
