#include "Map.h"
#include"TinyXML\tinyxml.h"


Map::Map()
{
}

Map::Map(Graphic* graphic)
{
	
	//load tileset lên
	info = new InfoMap(MapXML);
	this->tileset = new TileSet(graphic,info->tileCount, info->tileColumns, info->tileWidth, info->tileHeight);
	position = D3DXVECTOR2(0, 0);
}

Map::~Map()
{
	delete tileset;
	delete info;
}

void Map::Update(float gameTime)
{

}

InfoMap* Map::GetInfoMap()
{
	return info;
}

int Map::GetData(D3DXVECTOR2 position)
{
	int w = position.x / info->tileWidth;
	int h = position.y / info->tileHeight;
	return info->data[h][w];
}
void Map::SetData(D3DXVECTOR2 position, int data)
{
	int w = position.x / info->tileWidth;
	int h = position.y / info->tileHeight;
	info->data[h][w] = data;
}

void Map::Render(Viewport * view)
{
	for (int h = 0; h < info->height; h++)
		for (int w = 0; w < info->width; w++)
		{
			int id = info->data[h][w];
			if (id > 0 && id < 90)
			{
				D3DXVECTOR2 position(w * info->tileWidth, (h + 1) * info->tileHeight);
				tileset->Render(view, id, position);
			}
		}
}
