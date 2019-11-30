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
	CGrid(int MapWidth, int MapHeight, LPCSTR fileitem);
	void AddObject(LPGAMEOBJECT Object);

	//void AddObjectToGrid(LPCSTR fileitem);

	vector<LPGAMEOBJECT> GetListMapObject();

	void RemoveObject(LPGAMEOBJECT obj);
	

	vector<LPGAMEOBJECT> GetListObjectCanContactWith(LPGAMEOBJECT object);
	vector<LPGAMEOBJECT> GetListObjectCanContactWithMapObject(LPGAMEOBJECT object);

	vector<LPGAMEOBJECT> GetListEnemies();

	void RemoveAll(LPGAMEOBJECT obj);

	void MoveObject(LPGAMEOBJECT obj,float OldX, float OldY);
};