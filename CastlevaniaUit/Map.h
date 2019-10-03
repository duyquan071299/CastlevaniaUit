#pragma once
#include <fstream>
#include <sstream>
#include <d3dx9.h>
#include <string.h>
#include "Sprites.h"

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

class CMap
{
private:
	int ** Matrix; // map data
	int Columns, Rows; // cols and rows of our map
	int TileWidth, TileHeight;
	int MapWidth, MapHeight;
	//int currentBackground;
	LPSPRITE TileSet;
	vector<LPSPRITE> listTileSet;
	vector<LPCSTR> listMapData;



	void LoadMatrixBackground(LPCSTR fileMatrixMap);

	//vector<LPGAMEOBJECT> LoadMapObject(LPCSTR fileStaticObject);
	//vector<EnemySpawner *> LoadEnemySpawner(LPCSTR fileEnemies);
	
public:
	void DrawTileBackground();
	CMap(LPCSTR fileMatrixMap, LPCSTR fileTileSet);

	~CMap();

	void AddTileSet(LPCSTR fileMatrixMap, LPCSTR fileTileSet);

	//void SetCurrentBackground(int currentBackground);

	void Draw();

	int GetMapWidth() { return this->MapWidth; }
	int GetMapHeight() { return this->MapHeight; }

	//Grid * GetGrid() { return this->grid; }

	void Update(DWORD dt);
};
typedef CMap * LPMAP;
