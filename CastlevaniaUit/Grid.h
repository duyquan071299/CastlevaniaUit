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

	void BuildGrid(vector<LPGAMEOBJECT> listObject);

	vector<LPGAMEOBJECT> GetListMapObject();

	vector<LPGAMEOBJECT> GetListObjectCanContactWith(LPGAMEOBJECT object);

	vector<CEnemy *> GetListEnemies();

};