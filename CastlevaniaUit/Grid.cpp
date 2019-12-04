#include"Grid.h"
#include"Candle.h"
#include"Brick.h"
#include"Simon.h"
#include"Enemy.h"
#include"Panther.h"
#include"InvisibleObject.h"
#include"Camera.h"
#include"EffectDatabase.h"
#define CELL_WIDTH 256
#define CELL_HEIGHT 416

CGrid::CGrid(int MapWidth, int MapHeight, LPCSTR fileitem)
{
	this->Columns = MapWidth / CELL_WIDTH;
	this->Rows = (MapHeight / CELL_HEIGHT) +1;

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
	ifstream ifs(fileitem);
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
			case 5:
			{
				CPanther * Panther = new CPanther(x,y,holder);
				AddObject(Panther);
				break;

			}
			}
		}
		ifs.close();
	}

}


void CGrid::AddObjectToGrid(LPCSTR fileitem)
{
	int LeftCell, RightCell, TopCell, BottomCell;
	int type, x, y, holder, width, height;
	ifstream ifs(fileitem);
	ifs >>this->Columns >> this->Rows;
	CellMatrix = new CCell*[Rows];
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
	if (ifs.is_open()) {
		while (ifs.good())
		{
			ifs >>type >> x >> y >> width >> height >> holder;
			ifs >> LeftCell >> RightCell >> TopCell >> BottomCell;
			LPGAMEOBJECT Object;
			switch (type)
			{
			case 1:
			{
				CCandle* LargeCandle = new CCandle(x, y, static_cast<HolderType>(holder), 1);
				LargeCandle->SetWH(width, height);
				Object = dynamic_cast<CCandle*>(LargeCandle);
				break;
			}
			case 2:
			{
				CBrick* brick = new CBrick(x, y);
				brick->SetWH(width, height);
				brick->SetType(holder);
				Object = dynamic_cast<CBrick*>(brick);


				break;
			}
			case 3:
			{
				CCandle* SmallCandle = new CCandle(x, y, static_cast<HolderType>(holder), 2);
				SmallCandle->SetWH(width, height);
				Object = dynamic_cast<CCandle*>(SmallCandle);
				break;
			}
			case 4:
			{
				CInvisibleObject* Invisible = new CInvisibleObject(x, y);
				Invisible->SetType(holder);
				Invisible->SetWH(width, height);
				Object = dynamic_cast<CInvisibleObject*>(Invisible);
				break;
			}
			case 5:
			{
				CPanther * Panther = new CPanther(x, y, holder);
				Object = dynamic_cast<CPanther*>(Panther);
				break;

			}
			default:
				Object = new CBrick(x,y);
				break;
			}
			for (int i = TopCell; i <= BottomCell; i++)
			{
				if (i < 0 || i >= Rows) continue;
				for (int j = LeftCell; j <= RightCell; j++)
				{

					if (j < 0 || j >= Columns) continue;
					else
					{
					
						CellMatrix[i][j].AddObject(Object);
					}
				
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
	
		CellMatrix = nullptr;
	}
}


void CGrid::AddObject(LPGAMEOBJECT Object)
{
	float bl, bt, br, bb;

	Object->GetBoundingBox(bl, bt, br, bb);

	int startCol = int(bl) / CELL_WIDTH;
	int endCol = int(br+bl) / CELL_WIDTH;
	int startRow = int(bt) / CELL_HEIGHT;
	int endRow = int(bb+bt) / CELL_HEIGHT;

	for (int i = startRow; i <= endRow; i++)
	{
		if (i < 0 || i >= Rows) continue;
		for (int j = startCol; j <= endCol; j++)
		{

			if (j < 0 || j >= Columns) continue;
			CellMatrix[i][j].AddObject(Object);
		}
	}
}

vector<LPGAMEOBJECT> CGrid::GetListMapObject()
{
	vector<LPGAMEOBJECT> returnList;

	RECT camRect = CCamera::GetInstance()->GetBound();

	int startCol = camRect.left / CELL_WIDTH;
	int endCol = (camRect.right-1) / CELL_WIDTH;
	int startRow = camRect.top / CELL_HEIGHT;
	int endRow = (camRect.bottom-1) / CELL_HEIGHT;

	

	//tru right, bottom di 1 de dam bao vi tri do ko thuoc cell ke tiep

	for (int i = startRow; i <= endRow; i++)
	{
		if (i < 0 || i >= Rows) continue;
		for (int j = startCol; j <= endCol; j++)
		{
			if (j < 0 || j >= Columns) continue;
			vector<LPGAMEOBJECT> listObj = CellMatrix[i][j].GetListObject();
			if (listObj.size() > 0)
			{
				returnList.insert(returnList.end(),
					listObj.begin(),
					listObj.end());
			}
		}
	}

	//loc nhung phan tu trung nhau
	sort(returnList.begin(), returnList.end());
	auto last = unique(returnList.begin(), returnList.end());
	returnList.erase(last, returnList.end());


	vector<LPGAMEOBJECT> list;

	//loai bo nhung phan tu khong can duoc Update
	for (int i = 0; i < returnList.size(); i++)
	{
		if(returnList[i]->IsInCamera())
		{
			if (dynamic_cast<CCandle *>(returnList[i]))
			{
				returnList[i]->isIncamera = true;
				if (returnList[i]->IsDead == true)
				{
					CItem * Holder = new CItem(dynamic_cast<CCandle *>(returnList[i])->GetHolder());
					Holder->AppearOnMap();
					Holder->SetPosition(returnList[i]->x, returnList[i]->y);
					this->RemoveObject(returnList[i]);
					this->AddObject(Holder);
					returnList.erase(returnList.begin() + i);
					returnList.push_back(Holder);
					i--;


				}

			}
			else if (dynamic_cast<CItem*>(returnList[i]))
			{
				if (!dynamic_cast<CItem*>(returnList[i])->isAppearOnMap)
				{
					dynamic_cast<CItem*>(returnList[i])->AppearOnMap();
				}
				if (returnList[i]->IsDead == true)
				{
					this->RemoveAll(returnList[i]);
					returnList.erase(returnList.begin() + i);
					i--;
				}
			}
			else if (dynamic_cast<CInvisibleObject*>(returnList[i]))
			{
				if (returnList[i]->IsDead == true)
				{
					this->RemoveObject(returnList[i]);
					returnList.erase(returnList.begin() + i);
					i--;
				}

			}
			else if (dynamic_cast<CWeapon *>(returnList[i]))
			{
				if (returnList[i]->IsDead == true)
				{
					this->RemoveAll(returnList[i]);
					returnList.erase(returnList.begin() + i);
					i--;
				}
			}
			else if (dynamic_cast<CEnemyBullet*>(returnList[i]))
			{
				if (returnList[i]->IsDead == true)
				{
					this->RemoveAll(returnList[i]);
					returnList.erase(returnList.begin() + i);
					i--;
				}
			}
			else if (dynamic_cast<CBrick*>(returnList[i]))
			{
				if (returnList[i]->IsDead == true && dynamic_cast<CBrick*>(returnList[i])->GetType() > 2)
				{

					CEffectDatabase::GetInstance()->AddBrokenBrickEffect(returnList[i]->x, returnList[i]->y);
					if (dynamic_cast<CBrick*>(returnList[i])->GetType() == 4)
					{
						CItem * Holder = new CItem(CHICKEN);
						Holder->AppearOnMap();
						Holder->SetPosition(returnList[i]->x, returnList[i]->y + 32);
						AddObject(Holder);
					}
					RemoveAll(returnList[i]);
					returnList.erase(returnList.begin() + i);
					i--;


				}

			}

			
		}
		else
		{
			if (dynamic_cast<CEnemy*>(returnList[i]))
			{
				if (dynamic_cast<CPanther*>(returnList[i]) && dynamic_cast<CPanther*>(returnList[i])->isSitting == true)
					continue;
				returnList[i]->isIncamera = false;
			}
			else if(dynamic_cast<CEnemyBullet*>(returnList[i]))
			{
				this->RemoveAll(returnList[i]);
				returnList.erase(returnList.begin() + i);
				i--;
			}
			else if (dynamic_cast<CWeapon *>(returnList[i]))
			{
				this->RemoveAll(returnList[i]);
				returnList.erase(returnList.begin() + i);
				i--;
					
			}
			else if (dynamic_cast<CCandle *>(returnList[i]))
			{
				returnList[i]->isIncamera = false;
			}
		
		}

	}

	return returnList;
}

vector<LPGAMEOBJECT> CGrid::GetListObjectCanContactWith(LPGAMEOBJECT object)
{

	float rectLeft, rectTop, Width, Height;

	object->GetBoundingBox(rectLeft, rectTop, Width, Height);
	vector<CGameObject*> objects;
	if (dynamic_cast<CBrick *>(object))
	{
		return objects;
	}
	int LeftCell = (rectLeft-2.0f)/CELL_WIDTH;
	int RightCell = (rectLeft+Width+2.0f) / CELL_WIDTH;
	int TopCell = (rectTop-2.0f) / CELL_HEIGHT;
	int BottomCell = (rectTop+Height+2.0f) / CELL_HEIGHT;	



	for (int i = TopCell; i <= BottomCell; i++)
	{
		if (i < 0 || i >= Rows) continue;
		for (int j = LeftCell; j <= RightCell; j++)
		{
			if (j < 0 || j >= Columns) continue;
			for (int x = 0; x < CellMatrix[i][j].GetListObject().size(); x++)
			{
				objects.push_back(CellMatrix[i][j].GetListObject().at(x));
			}
		}
	}


	sort(objects.begin(), objects.end());
	auto last = unique(objects.begin(), objects.end());
	objects.erase(last, objects.end());

	
	vector<LPGAMEOBJECT> list;

	for (int i = 0; i < objects.size(); i++)
	{
		if (dynamic_cast<CSimon*>(object))
		{
			if (dynamic_cast<CCandle *>(objects[i]) || (dynamic_cast<CWeapon *>(objects[i])&& !dynamic_cast<CEnemyBullet *>(objects[i])))
				continue;
			else if (dynamic_cast<CBrick*>(objects[i]))
			{
				if (dynamic_cast<CSimon*>(object)->isOnStair &&dynamic_cast<CSimon*>(object)->isUP && !dynamic_cast<CSimon*>(object)->isColiableWithStairBottom)
					continue;
				if (dynamic_cast<CSimon*>(object)->isOnStair && !dynamic_cast<CSimon*>(object)->isUP && dynamic_cast<CSimon*>(object)->isColiableWithStairTop)
					continue;


			}
			else if (dynamic_cast<CEnemy*>(objects[i]) && (dynamic_cast<CEnemy*>(objects[i])->isBurning || dynamic_cast<CSimon*>(object)->isUntouchable()))
				continue;
			else if (dynamic_cast<CEnemyBullet*>(objects[i]) && dynamic_cast<CSimon*>(object)->isUntouchable())
				continue;
			
		}
		
		list.push_back(objects[i]);
	}



	return list;
}

vector<LPGAMEOBJECT> CGrid::GetListObjectCanContactWithMapObject(LPGAMEOBJECT object)
{
	vector<LPGAMEOBJECT> objects;

	RECT camRect = CCamera::GetInstance()->GetBound();

	int startCol = camRect.left / CELL_WIDTH;
	int endCol = (camRect.right - 1) / CELL_WIDTH;
	int startRow = camRect.top / CELL_HEIGHT;
	int endRow = (camRect.bottom - 1) / CELL_HEIGHT;




	//tru right, bottom di 1 de dam bao vi tri do ko thuoc cell ke tiep

	for (int i = startRow; i <= endRow; i++)
	{
		if (i < 0 || i >= Rows) continue;
		for (int j = startCol; j <= endCol; j++)
		{
			if (j < 0 || j >= Columns) continue;
			vector<LPGAMEOBJECT> listObj = CellMatrix[i][j].GetListObject();
			if (listObj.size() > 0)
			{
				objects.insert(objects.end(),
					listObj.begin(),
					listObj.end());
			}
		}
	}

	//loc nhung phan tu trung nhau
	sort(objects.begin(), objects.end());
	auto last = unique(objects.begin(), objects.end());
	objects.erase(last, objects.end());


	vector<LPGAMEOBJECT> list;
	for (int i = 0; i < objects.size(); i++)
	{
		if (dynamic_cast<CEnemy *>(object))
		{
			if (dynamic_cast<CCandle *>(objects[i]) || dynamic_cast<CItem *>(objects[i]) || dynamic_cast<CEnemy *>(objects[i]))
				continue;
			else if (dynamic_cast<CInvisibleObject *>(objects[i]))
			{
				if (dynamic_cast<CInvisibleObject *>(objects[i])->GetType() != PANTHER_JUMP_OBJECT)
					continue;
			}

			if (dynamic_cast<CInvisibleObject *>(objects[i]) && dynamic_cast<CInvisibleObject *>(objects[i])->GetType() == PANTHER_JUMP_OBJECT && dynamic_cast<CPanther *>(object))
			{
				if(dynamic_cast<CPanther *>(object)->isJumping || dynamic_cast<CPanther *>(object)->isFalling)
					continue;
			}
				
		}
		else if (dynamic_cast<CDagger *>(object))
		{
			if (((dynamic_cast<CCandle *>(objects[i])) || dynamic_cast<CItem *>(objects[i])) && (objects[i]->isColiable == false || !objects[i]->isIncamera))
				continue;
			else if ((dynamic_cast<CBrick *>(objects[i])) || (dynamic_cast<CInvisibleObject *>(objects[i])))
				continue;
			else if (dynamic_cast<CWeapon *>(objects[i]))
				continue;
		}
		else if (dynamic_cast<CHolyWater *>(object))
		{
			if (dynamic_cast<CInvisibleObject *>(objects[i]) || dynamic_cast<CItem *>(objects[i]))
				continue;
			else if (dynamic_cast<CEnemy *>(objects[i]) && dynamic_cast<CEnemy *>(objects[i])->isBurning)
				continue;
			else if (dynamic_cast<CWeapon *>(objects[i]))
				continue;
		}
		else if (dynamic_cast<CItem *>(object))
		{
			if (!dynamic_cast<CBrick*>(objects[i]))
				continue;
		}
	
		list.push_back(objects[i]);
	}
	return list;

}
vector<LPGAMEOBJECT>  CGrid::GetListEnemies()
{
	vector<LPGAMEOBJECT> returnList;

	RECT camRect = CCamera::GetInstance()->GetBound();

	int startCol = camRect.left / CELL_WIDTH;
	int endCol = (camRect.right - 1) / CELL_WIDTH;
	int startRow = camRect.top / CELL_HEIGHT;
	int endRow = ((camRect.bottom -1) / CELL_HEIGHT)+1;



	//tru right, bottom di 1 de dam bao vi tri do ko thuoc cell ke tiep

	for (int i = startRow; i <= endRow; i++)
	{
		if (i < 0 || i >= Rows) continue;
		for (int j = startCol; j <= endCol; j++)
		{
			if (j < 0 || j >= Columns) continue;
			vector<LPGAMEOBJECT> listObj = CellMatrix[i][j].GetListObject();
			if (listObj.size() > 0)
			{
				returnList.insert(returnList.end(),
					listObj.begin(),
					listObj.end());
			}
		}
	}

	//loc nhung phan tu trung nhau
	sort(returnList.begin(), returnList.end());
	auto last = unique(returnList.begin(), returnList.end());
	returnList.erase(last, returnList.end());

	vector<LPGAMEOBJECT > EnemyList;
	for (int i = 0; i < returnList.size(); i++)
	{
		if (returnList[i]->IsInCamera())
		{
			if (dynamic_cast<CEnemy *>(returnList[i]))
			{
				EnemyList.push_back(returnList[i]);
			}
		}
		else
		{
			if (dynamic_cast<CEnemy*>(returnList[i]))
			{
				if (dynamic_cast<CPanther*>(returnList[i]) && dynamic_cast<CPanther*>(returnList[i])->isSitting == true)
					continue;
				returnList[i]->isIncamera = false;
				EnemyList.push_back(returnList[i]);
			}
		}
		

	}
	return EnemyList;

}

void CGrid::RemoveObject(LPGAMEOBJECT obj)
{
	float rectLeft, rectTop, Width, Height;

	obj->GetBoundingBox(rectLeft, rectTop, Width, Height);
	vector<CGameObject*> objects;

	int LeftCell = rectLeft / CELL_WIDTH;
	int RightCell = (rectLeft + Width) / CELL_WIDTH;
	int TopCell = rectTop / CELL_HEIGHT;
	int BottomCell = (rectTop + Height) / CELL_HEIGHT;


	for (int i = TopCell; i <= BottomCell; i++)
	{
		if (i < 0 || i >= Rows) continue;
		for (int j = LeftCell; j <= RightCell; j++)
		{
			if (j < 0 || j >= Columns) continue;
			CellMatrix[i][j].RemoveObject(obj);
		}
	}
}
void CGrid::RemoveAll(LPGAMEOBJECT obj)
{/*
	RECT camRect = CCamera::GetInstance()->GetBound();

	int startCol = (camRect.left / CELL_WIDTH)-2;
	int endCol = ((camRect.right - 1) / CELL_WIDTH)+2;
	int startRow = (camRect.top / CELL_HEIGHT)-2;
	int endRow = ((camRect.bottom - 1) / CELL_HEIGHT)+2;*/

	for (int i = 0; i < Rows; i++)
	{
		if (i < 0 || i >= Rows) continue;
		for (int j = 0; j <= Columns; j++)
		{
			if (j < 0 || j >= Columns) continue;
			CellMatrix[i][j].RemoveObject(obj);
		}
	}
}
void CGrid::MoveObject(LPGAMEOBJECT obj, float OldX, float OldY)
{
	if (dynamic_cast<CBrick*>(obj) || dynamic_cast<CInvisibleObject*>(obj))
		return;
	float rectLeft, rectTop, Width, Height;

	obj->GetBoundingBox(rectLeft, rectTop, Width, Height);
	int oldLeftCell = OldX / CELL_WIDTH;
	int oldRightCell = (OldX +Width) / CELL_WIDTH;
	int oldTopCell = OldY / CELL_HEIGHT;
	int oldBottomCell = (OldY + Height) / CELL_HEIGHT;
	



	int LeftCell = rectLeft / CELL_WIDTH;
	int RightCell = (rectLeft+Width) / CELL_WIDTH;
	int TopCell = rectTop / CELL_HEIGHT;
	int BottomCell = (rectTop + Height) / CELL_HEIGHT;

	if (oldLeftCell >= Columns || oldRightCell < 0 || oldTopCell<0 || oldBottomCell>=Rows)
	{
		return;
	}
	


	if (!(oldLeftCell < 0 || oldRightCell >= Columns || oldTopCell >= Rows || oldBottomCell < 0))
	{
	
		if (LeftCell < oldLeftCell)
		{
			
			if (oldTopCell < Rows)
			{
				CellMatrix[oldTopCell][oldLeftCell].RemoveObject(obj);
			}

			if (oldTopCell != oldBottomCell)
			{
				CellMatrix[oldBottomCell][oldLeftCell].RemoveObject(obj);
			}
		}

		if (RightCell > oldRightCell)
		{
			if (oldTopCell < Rows)
			{
				CellMatrix[oldTopCell][oldRightCell].RemoveObject(obj);
			}

			if (oldTopCell != oldBottomCell)
			{
				CellMatrix[oldBottomCell][oldRightCell].RemoveObject(obj);
			}
		}

		if (TopCell < oldTopCell)
		{
			if (oldLeftCell >= 0)
			{
				CellMatrix[oldTopCell][oldLeftCell].RemoveObject(obj);
			}

			if (oldLeftCell != oldRightCell)
			{
				CellMatrix[oldTopCell][oldRightCell].RemoveObject(obj);
			}
		}

		if (BottomCell > oldBottomCell)
		{
			if (oldLeftCell >= 0)
			{
				CellMatrix[oldBottomCell][oldLeftCell].RemoveObject(obj);
			}

			if (oldLeftCell != oldRightCell)
			{
				CellMatrix[oldBottomCell][oldRightCell].RemoveObject(obj);
			}
		}

		if (TopCell < Rows &&TopCell>=0)
		{
			if (LeftCell < Columns &&LeftCell >= 0)
			{
				CellMatrix[TopCell][LeftCell].AddObject(obj);
			}

			if (LeftCell != RightCell && RightCell < Columns && RightCell>=0)
			{
				CellMatrix[TopCell][RightCell].AddObject(obj);
			}
		}

		if (BottomCell < Rows &&BottomCell >= 0)
		{
			if (LeftCell < Columns &&LeftCell >= 0)
			{
				CellMatrix[BottomCell][LeftCell].AddObject(obj);
			}

			if (LeftCell != RightCell && RightCell < Columns && RightCell >= 0)
			{
				CellMatrix[BottomCell][RightCell].AddObject(obj);
			}
		}
	}


}