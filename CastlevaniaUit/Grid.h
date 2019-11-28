#pragma once
#include"Cell.h"
#include"Enemy.h"

class CGrid
{
private:
	CCell** CellMatrix;
	int Columns;
	int Rows;
public:

	CGrid();
	~CGrid();
	CGrid(int MapWidth, int MapHeight);
	void AddObject(LPGAMEOBJECT Object);



	unordered_set<LPGAMEOBJECT> GetListMapObject();

	unordered_set<LPGAMEOBJECT> GetListObjectCanContactWith(LPGAMEOBJECT object);

	unordered_set<CEnemy *> GetListEnemies();

};