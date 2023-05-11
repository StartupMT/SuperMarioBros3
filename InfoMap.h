#pragma once
#include <d3dx9.h>
#include "TinyXML\tinyxml.h"
#include<string>
#include<vector>
using namespace std;
class InfoMap
{
public:
	string layerName;
	int data[50][200];
	int width, height, tileCount, tileColumns, numObjectGroups;
	float tileWidth, tileHeight;
	InfoMap(const char* path);
	~InfoMap();
	void ReadXMl(const char* path);

	int GetData(D3DXVECTOR2 pos);
	void SetData(D3DXVECTOR2 position, int Data);
};
