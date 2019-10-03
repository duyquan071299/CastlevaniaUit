#pragma once
#include "Map.h"

class CMapFactory
{
private:
	std::vector<LPMAP> maps;
	static CMapFactory* instance;

public:
	void LoadResources();
	LPMAP GetMap(int level);
	static CMapFactory* GetInstance();
};