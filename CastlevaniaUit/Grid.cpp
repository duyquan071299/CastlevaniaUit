#include"Grid.h"
#include"Candle.h"
#include"Brick.h"
#include"Enemy.h"
#include"InvisibleObject.h"
#include"Camera.h"
#define CELL_WIDTH 256
#define CELL_HEIGHT 352

CGrid::CGrid(int MapWidth, int MapHeight)
{
	this->Columns = MapWidth / CELL_WIDTH;
	this->Rows = MapHeight / CELL_HEIGHT;
	if (this->Rows == 0)
		this->Rows = 1;
	CellMatrix=new CCell*[Rows];
	for (int i = 0; i < Rows; i++)
	{
		CellMatrix[i] = new CCell[Columns];
	}

	
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Columns; j++)
		{
			CellMatrix[i][j].SetID(Columns * i + j);
		}
	}

	int type, x, y, holder, width, height;
	ifstream ifs("Resources\\Maps\\Scene1_Object.txt");
	if (ifs.is_open()) {
		while (ifs.good()) {
			ifs >> type >> x >> y >> width >> height >> holder;
			switch (type)
			{
			case 1:
			{
				CCandle* LargeCandle = new CCandle(x, y, static_cast<HolderType>(holder), 1);
				LargeCandle->SetWH(width, height);
				AddObject(LargeCandle);
				break;
			}
			case 2:
			{
				CBrick* brick = new CBrick(x, y);
				brick->SetWH(width, height);
				brick->SetType(holder);
				AddObject(brick);
	

				break;
			}
			case 3:
			{
				CCandle* LargeCandle = new CCandle(x, y, static_cast<HolderType>(holder), 2);
				LargeCandle->SetWH(width, height);
				AddObject(LargeCandle);
				break;
			}
			case 4:
			{
				CInvisibleObject* Invisible = new CInvisibleObject(x, y);
				Invisible->SetType(holder);
				Invisible->SetWH(width, height);
				AddObject(Invisible);
				break;
			}
			}
		}
		ifs.close();
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
	int endCol = int(br+bl - 1) / CELL_WIDTH;
	int startRow = int(bt) / CELL_HEIGHT;
	int endRow = int(bb+bt - 1) / CELL_HEIGHT;

	for (int i = startRow; i <= endRow; i++)
	{
		for (int j = startCol; j <= endCol; j++)
		{
			CellMatrix[i][j].AddObject(Object);
		}
	}
}

//unordered_set<LPGAMEOBJECT> GetListMapObject()
//{
//
//}
unordered_set<LPGAMEOBJECT> CGrid::GetListObjectCanContactWith(LPGAMEOBJECT object)
{
	float rectLeft, rectTop, Width, Height;

	object->GetBoundingBox(rectLeft, rectTop, Width, Height);
	std::unordered_set<CGameObject*> objects;

	int LeftCell = rectLeft / CELL_WIDTH;
	int RightCell = (rectLeft+Width) / CELL_WIDTH;
	int TopCell = rectTop / CELL_HEIGHT;
	int BottomCell = (rectTop+Height) / CELL_HEIGHT;	


	for (int i = BottomCell; i <= TopCell; i++)
	{
		if (i < 0 || i >= Rows) continue;
		for (int j = LeftCell; j <= RightCell; j++)
		{
			if (j < 0 || j >= Columns) continue;
			for (int x = 0; x < CellMatrix[i][j].GetListObject().size(); x++)
			{
				objects.insert(CellMatrix[i][j].GetListObject().at(x));
			}
		}
	}
	return objects;
}
