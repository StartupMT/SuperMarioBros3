#pragma once
#include<string>
#include "TinyXML\tinyxml.h"
#include <vector>
#include "MapObject.h"

using namespace std;

class MapObjectGroup
{
public:
	vector<MapObject*> Objects;
	MapObjectGroup(TiXmlElement* node);
	~MapObjectGroup();
	void ReadXML(TiXmlElement* node);
};