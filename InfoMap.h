#pragma once
#include <d3dx9.h>
#include "TinyXML\tinyxml.h"
#include<string>
#include<vector>
#include<map>
using namespace std;
class InfoMap
{
protected:
	map<int, map<int, int>> data;

public:
	int width, height, tileCount, tileColumns;
	float tileWidth, tileHeight;
	InfoMap(const char *path);
	~InfoMap();
	void ReadXMl(const char *path);

	int GetData(int w, int h);
	void SetData(int w, int h, int Data);
};
