#include"Grid.h"
#include"Camera.h"
#define CELL_WIDTH SCREEN_WIDTH / 2
#define CELL_HEIGHT SCREEN_HEIGHT / 2

CGrid::CGrid(int MapWidth, int MapHeight)
{
	this->Columns = MapWidth / CELL_WIDTH;
	this->Rows = MapHeight /CELL_HEIGHT;
	CellMatrix=new CCell*[Rows];
	for (int i = 0; i < Rows; i++)
	{
		CellMatrix[i] = new CCell[Columns];
	}

	
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Rows; j++)
		{
			CellMatrix[0][0].SetID(Columns * i + j);
		}
	}

}

CGrid::CGrid()
{

}



CGrid::~CGrid()
{
	if (CellMatrix)
	{
		for (int i = 0; i < Rows; i++)
		{
			delete CellMatrix[i];
		}
		delete CellMatrix;
		CellMatrix = nullptr;
	}
}


void CGrid::AddObject(LPGAMEOBJECT Object)
{
	float bl, bt, br, bb;

	Object->GetBoundingBox(bl, bt, br, bb);

	int startCol = int(bl) / CELL_WIDTH;
	int endCol = int(br - 1) / CELL_WIDTH;
	int startRow = int(bt) / CELL_HEIGHT;
	int endRow = int(bb - 1) / CELL_HEIGHT;

	for (int i = startRow; i <= endRow; i++)
	{
		for (int j = startCol; j <= endCol; j++)
		{
			CellMatrix[i][j].AddObject(Object);
		}
	}
}

void CGrid::BuildGrid(vector<LPGAMEOBJECT> listObject)
{
	for (int i = 0; i < listObject.size(); i++)
	{
		AddObject(listObject[i]);
	}
}

//vector<LPGAMEOBJECT> CGrid::GetListMapObject()
//{
//
//}
//
//vector<LPGAMEOBJECT> CGrid::GetListObjectCanContactWith(LPGAMEOBJECT object)
//{
//}
//
//vector<CEnemy *> CGrid::GetListEnemies()
//{
//
//}