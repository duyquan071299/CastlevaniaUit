#include "Map.h"

CMap::CMap(const char* filePath)
{
	LoadMap(filePath);
}

CMap::~CMap()
{
	delete mMap;
}

void CMap::LoadMap(const char* filePath)
{
	mMap = new Tmx::Map();
	mMap->ParseFile(filePath);

	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = this->GetWidth();
	r.bottom = this->GetHeight();

	for (size_t i = 0; i < mMap->GetNumTilesets(); i++)
	{
		const Tmx::Tileset *tileset = mMap->GetTileset(i);

		//LPSPRITE sprite = new CSprite(tileset->GetImage()->GetSource().c_str());

		//mListTileset.insert(std::pair<int, LPSPRITE>(i, sprite));
	}
}

Tmx::Map* CMap::GetMap()
{
	return mMap;
}

int CMap::GetWidth()
{
	return mMap->GetWidth() * mMap->GetTileWidth();
}

int CMap::GetHeight()
{
	return mMap->GetHeight() * mMap->GetTileHeight();
}

int CMap::GetTileWidth()
{
	return mMap->GetTileWidth();
}

int CMap::GetTileHeight()
{
	return mMap->GetTileHeight();
}

void CMap::Draw()
{
	for (size_t i = 0; i < mMap->GetNumTileLayers(); i++)
	{
		const Tmx::TileLayer *layer = mMap->GetTileLayer(i);

		if (!layer->IsVisible())
		{
			continue;
		}

		RECT sourceRECT;

		int tileWidth = mMap->GetTileWidth();
		int tileHeight = mMap->GetTileHeight();

		for (size_t m = 0; m < layer->GetHeight(); m++)
		{
			for (size_t n = 0; n < layer->GetWidth(); n++)
			{
				int tilesetIndex = layer->GetTileTilesetIndex(n, m);

				if (tilesetIndex != -1)
				{
					const Tmx::Tileset *tileSet = mMap->GetTileset(tilesetIndex);

					int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
					int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;

					//LPSPRITE sprite = mListTileset[layer->GetTileTilesetIndex(n, m)];

					//tile index
					int tileID = layer->GetTileId(n, m);

					int y = tileID / tileSetWidth;
					int x = tileID - y * tileSetWidth;

					sourceRECT.top = y * tileHeight;
					sourceRECT.bottom = sourceRECT.top + tileHeight;
					sourceRECT.left = x * tileWidth;
					sourceRECT.right = sourceRECT.left + tileWidth;

					//tru tilewidth/2 va tileheight/2 vi Sprite ve o vi tri giua hinh anh cho nen doi hinh de cho
					//dung toa do (0,0) cua the gioi thuc la (0,0) neu khong thi se la (-tilewidth/2, -tileheigth/2);
					D3DXVECTOR3 position(n * tileWidth + tileWidth / 2, m * tileHeight + tileHeight / 2, 0);

					//sprite->SetWidth(tileWidth);
					//sprite->SetHeight(tileHeight);

					//sprite->Draw(position, sourceRECT, D3DXVECTOR2());
				}
			}
		}
	}
}