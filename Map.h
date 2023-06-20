﻿#pragma once
#include "Viewport.h"
#include "TileSet.h"
#include "GameDefine.h"
#include "InfoMap.h"
#include "Enemy.h"
#include "Block.h"
#include "RedKoopa.h"
#include "SuperLeaf.h"

using namespace Define;

class Map
{
public:
	//tính theo tile
	int WidthMap, HeightMap;
	TileSet* tileset;
	D3DXVECTOR2 position;
	InfoMap* info;
	map<string, int> objectTag;
	vector <Object*> ListObject;
public:
	Map();
	~Map();

	Object* CreateObject(MapObject* _mapobject);

	void Update(float gameTime);
	void Render(Viewport* view);
};

