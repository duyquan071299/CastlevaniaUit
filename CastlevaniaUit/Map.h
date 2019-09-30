#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "Sprites.h"
#include "MapReader/tmx.h.in"
#include "GlobalObject.h"

class CMap
{
public:
	CMap(const char* filePath);

	Tmx::Map* GetMap();

	int GetWidth();
	int GetHeight();
	int GetTileWidth();
	int GetTileHeight();

	void Draw();

	~CMap();

private:
	void LoadMap(const char* filePath);

	Tmx::Map                        *mMap;
	std::map<int, LPSPRITE>          mListTileset;
};


