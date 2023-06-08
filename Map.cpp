#include "Map.h"
#include"TinyXML\tinyxml.h"


Map::Map()
{
	//load tileset lên
	info = new InfoMap(MapXML);
	this->tileset = new TileSet(info->tileCount, info->tileColumns, info->tileWidth, info->tileHeight);
	position = D3DXVECTOR2(0, 0);

	objectTag["Goomba"] = Enemy::Goomba;
	objectTag["Wall"] = Block::Wall;
	// objectTag["Wall1"] = Wall::ghost;

	for (int i = 0; i < info->numObjectGroups; i++)
	{
		for (int j = 0; j < info->ObjectGroups.at(i)->NumOnjects; j++)
		{
			ListObject.push_back(CreateObject(info->ObjectGroups.at(i)->Objects.at(j)));
		}
	}
}

Map::~Map()
{
	delete tileset;
	delete info;
	for (size_t i = 0; i < ListObject.size(); i++)
	{
		delete ListObject.at(i);
	}
}

void Map::Update(float gameTime)
{

}

Object* Map::CreateObject(MapObject* _mapobject)
{
	D3DXVECTOR2 pos;
	pos.x = _mapobject->x + _mapobject->width / 2;
	pos.y = info->height * info->tileHeight - _mapobject->y - _mapobject->height / 2;

	Object* obj;
	Object::tag tagg = Object::GetTag(_mapobject->name);
	switch (tagg)
	{
	case Object::Enemy:
		obj = new Enemy();
		break;
	case Object::Block:
		obj = new Block();
		break;
	default:
		obj = new Object();
		break;
	}
	obj->Init(pos, objectTag[_mapobject->name], _mapobject->kind);
	obj->GetBound(_mapobject->width, _mapobject->height);
	return obj;
}

void Map::Render(Viewport * view)
{
	int startH, startW, endH, endW;
	RECT r = view->GetBoundViewport();
	startH = r.bottom / info->tileHeight;
	endH = r.top / info->tileHeight + 1;
	startW = r.left / info->tileWidth;
	endW = r.right / info->tileWidth + 1;

	for (int h = startH; h < endH; h++)
		for (int w = startW; w < endW; w++)
		{
			int id = info->GetData(w, h);
			if (id > 0)
			{
				D3DXVECTOR2 position(w * info->tileWidth, (h + 1) * info->tileHeight);
				tileset->Render(view, id, position);
			}
		}
}
