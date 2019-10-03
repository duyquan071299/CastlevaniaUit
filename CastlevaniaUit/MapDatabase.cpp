#include "MapDatabase.h"

CMapFactory* CMapFactory::instance = NULL;

void CMapFactory::LoadResources()
{
	for (int i = 1; i <= 3; ++i)
	{
		//maps.push_back(new CMap());
		
	}
}

LPMAP CMapFactory::GetMap(int level)
{
	return maps[level - 1];
}

CMapFactory * CMapFactory::GetInstance()
{
	if (instance == NULL)
		instance = new CMapFactory();
	return instance;
}