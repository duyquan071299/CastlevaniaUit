#include "Map.h"

CMap::CMap(LPCSTR fileMatrixMap, LPCSTR fileTileSet)
{
	TileWidth = TILE_WIDTH;
	TileHeight = TILE_HEIGHT;

	if (fileMatrixMap != "")
	{
		/*AddTileSet(fileMatrixMap, fileTileSet);*/
		LoadMatrixBackground(fileMatrixMap);
		TileTexture = (new CTextures(fileTileSet, D3DCOLOR_XRGB(255, 0, 255)))->GetTexture();
		
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
//
//void CMap::AddTileSet(LPCSTR fileMatrixMap, LPCSTR fileTileSet)
//{
//	
//	//listTileSet.push_back(new CSprite(fileTileSet));
//	//listMapData.push_back(fileMatrixMap);
//}

void CMap::LoadMatrixBackground(LPCSTR fileMatrixMap)
{
	ifstream ifs(fileMatrixMap);
	ifs >> Columns >> Rows>> MapCol;
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
	
	
	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Columns; j++)
		{

		
			//RECT objRECT;
			//objRECT.left = j * 32;
			//objRECT.top = i * 32;
			//objRECT.right = objRECT.left + TileWidth;
			//objRECT.bottom = objRECT.top + TileHeight;

			////neu nam ngoai camera thi khong Draw
			//if (!isContain(objRECT, CCamera::GetInstance()->GetBound()))
			//	continue;
			delete TileSet;
			TileSet = new CSprite(MAP, Matrix[i][j] - 1, MapCol);
			TileSet->Settexture(TileTexture);
			TileSet->SetFrameWH(32, 32);
			TileSet->Draw((float)j * 32, (float)i * 32 +80, default_color);

		}
	

	


}



void CMap::Draw()
{
	DrawTileBackground();

}

void CMap::Update(DWORD dt)
{








}

bool CMap::isContain(RECT rect1, RECT rect2)
{
	if (rect1.left > rect2.right || rect1.right < rect2.left || rect1.top > rect2.bottom || rect1.bottom < rect2.top)
	{
		return false;
	}

	return true;
}


