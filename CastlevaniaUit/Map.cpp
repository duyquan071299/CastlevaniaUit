#include "Map.h"


CMap::CMap(LPCSTR fileMatrixMap, LPCSTR fileTileSet, LPCSTR fileItemMap)
{
	TileWidth = TILE_WIDTH;
	TileHeight = TILE_HEIGHT;
	//currentBackground = 0;

	if (fileMatrixMap != "")
	{
		AddTileSet(fileMatrixMap, fileTileSet);
		LoadMatrixBackground(fileMatrixMap);
		
	}
	else
	{
		//mapWidth = ViewPort::GetInstance()->GetCameraWidth();
		//mapHeight = ViewPort::GetInstance()->GetCameraHeight();
	}
	 this->listObject = LoadMapObject(fileItemMap);
	

}

CMap::~CMap()
{
	if (Matrix)
	{
		for (int i = 0; i < Rows; i++)
		{
			delete Matrix[i];
		}
		delete Matrix;
		Matrix = nullptr;
	}

}

void CMap::AddTileSet(LPCSTR fileMatrixMap, LPCSTR fileTileSet)
{
	
	//listTileSet.push_back(new CSprite(fileTileSet));
	//listMapData.push_back(fileMatrixMap);
}

void CMap::LoadMatrixBackground(LPCSTR fileMatrixMap)
{
	ifstream ifs(fileMatrixMap);
	ifs >> Columns >> Rows;
	Matrix = new int*[Rows];
	for (int i = 0; i < Rows; i++) {
		Matrix[i] = new int[Columns];
	}	
	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Columns; j++)
			ifs >> Matrix[i][j];

	MapWidth = Columns* TileWidth;
	MapHeight = Rows * TileHeight;
}


void CMap::DrawTileBackground()
{
	//RECT tileRect;
	//D3DXVECTOR2 trans = D3DXVECTOR2(SCREEN_WIDTH / 2 - CCamera::GetInstance()->GetPosition().x,
	//	SCREEN_HEIGHT / 2 - CCamera::GetInstance()->GetPosition().y);
	
		for (int i = 0; i < Rows; i++)
			for (int j = 0; j < Columns; j++)
			{

				//D3DXVECTOR3 position(j * TileWidth + TileWidth / 2, i * TileHeight + tileHeight / 2, 0);

				RECT objRECT;
				objRECT.left = j*32;	
				objRECT.top =  i*32;
				objRECT.right = objRECT.left+TileWidth;
				objRECT.bottom = objRECT.top+TileHeight;

				//neu nam ngoai camera thi khong Draw
				if (!isContain(objRECT, CCamera::GetInstance()->GetBound()))
					continue;
			
					TileSet = new CSprite(MAP, Matrix[i][j] - 1, 49);
					TileSet->Settexture(CTextureDatabase::GetInstance()->GetTexture(MAP));
					TileSet->SetFrameWH(32, 32);
					TileSet->Draw((float)j * 32, (float)i * 32);
				
				
			
				


				
			}

	


}

void CMap::DrawObject()
{
	for (int i = 0; i < listObject.size(); i++)
	{
		RECT objRECT;
		objRECT.left = listObject[i]->x;
		objRECT.top = listObject[i]->y;
		objRECT.right = objRECT.left + TileWidth;
		objRECT.bottom = objRECT.top + TileHeight;
		if (!isContain(objRECT, CCamera::GetInstance()->GetBound()))
			continue;
		listObject[i]->Render();
	}
}

void CMap::Draw()
{
	DrawTileBackground();
	DrawObject();

	//vector<LPGAMEOBJECT> mapObjects = grid->GetListMapObjectInViewPort();

	//for (int i = 0; i < mapObjects.size(); i++)
	//{
		//mapObjects[i]->Render();
	//}
}

void CMap::Update(DWORD dt)
{
	//Update animation here
	//vector<LPGAMEOBJECT> mapObjects = grid->GetListMapObjectInViewPort();

	//for (int i = 0; i < mapObjects.size(); i++)
	//{
		//mapObjects[i]->Update(dt);
	//}
	
}

bool CMap::isContain(RECT rect1, RECT rect2)
{
	if (rect1.left > rect2.right || rect1.right < rect2.left || rect1.top > rect2.bottom || rect1.bottom < rect2.top)
	{
		return false;
	}

	return true;
}
vector<LPGAMEOBJECT> CMap::LoadMapObject(LPCSTR fileItemMap)
{
	int type, x, y;
	vector<LPGAMEOBJECT> listObject;
	ifstream ifs(fileItemMap);
	if (ifs.is_open()) {
		while (ifs.good()) {
			ifs >> type >> x >> y;
			switch (type)
			{
			case 1:
			{
				CLargeCandle* LargeCandle = new CLargeCandle();
				LargeCandle->SetPosition(x, y);
				listObject.push_back(LargeCandle);
				break;
			}
			case 2:
			{

			}
			}
		}
		ifs.close();
	}
		for (int j = 0; j < Columns; j++)
		{
			if (Matrix[9][j] == 49)
			{
				CBrick* brick = new CBrick();
				brick->x = (float)j * 32;
				brick->y = (float)9 * 32;
				brick->SetSprite(new CSprite(MAP, Matrix[9][j] - 1, 49));
				brick->GetSprite()->SetFrameWH(32, 32);
				brick->GetSprite()->Settexture(CTextureDatabase::GetInstance()->GetTexture(MAP));
				listObject.push_back(brick);

			}
		}



	return listObject;
}

