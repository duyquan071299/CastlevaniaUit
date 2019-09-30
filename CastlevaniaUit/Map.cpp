#include "Map.h"


CMap::CMap(LPCSTR fileMatrixMap, LPCSTR fileTileSet)
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
	RECT tileRect;
	D3DXVECTOR3 camPos(0,0 ,0);// ViewPort::GetInstance()->GetCameraPos()

	int cameraWidth = 0; //ViewPort::GetInstance()->GetCameraWidth();
	int cameraHeight = 0;// ViewPort::GetInstance()->GetCameraHeight();


	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Columns; j++)
		{
			TileSet = new CSprite(MAP, Matrix[i][j] - 1, Columns);
			TileSet->Settexture(CTextureDatabase::GetInstance()->GetTexture(MAP));
			TileSet->SetFrameWH(32, 32);
			TileSet->Draw(j * 32, i * 32);
		}


	/*int colStart = (int)camPos.x / TileWidth;
	int colEnd = colStart + 16 < Columns - 1 ? colStart + 16 : Columns - 1;
	int rowStart = (int)(camPos.y) / TileHeight;
	int rowEnd = rowStart + 15 < Rows - 1 ? rowStart + 15 : Rows - 1;

	if (colStart >= 0 && rowStart >= 0)
	{
		for (int i = rowStart; i <= rowEnd; i++)
		{
			for (int j = colStart; j <= colEnd; j++)
			{
				//tileRect dung de lay ra RECT trong tile set de ve
				tileRect.left = (Matrix[i][j] % 16) * TileWidth;
				tileRect.top = (Matrix[i][j] / 16) * TileHeight;
				tileRect.right = tileRect.left + TileWidth;
				tileRect.bottom = tileRect.top + TileHeight;

				//cast pos to int-type to avoid tearing CMap
				//listTileSet[currentBackground]->SetCenter(D3DXVECTOR3(0, 0, 0));
				//listTileSet[currentBackground]->Draw(D3DXVECTOR3(j * tileWidth, i * tileHeight, 0), tileRect);
			}
		}
	}*/

}

void CMap::Draw()
{
	DrawTileBackground();

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