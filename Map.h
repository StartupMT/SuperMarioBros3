#pragma once
#include "Viewport.h"
#include "TileSet.h"
#include "GameDefine.h"
#include "InfoMap.h"
using namespace Define;

class Map
{
protected:
	//tính theo tile
	int WidthMap, HeightMap;
	TileSet* tileset;
	D3DXVECTOR2 position;
	InfoMap *info;

public:
	Map();
	~Map();
	InfoMap *GetInfoMap();

	void Update(float gameTime);
	void Render(Viewport * view);
};

