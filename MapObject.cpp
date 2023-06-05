#include "MapObject.h"

MapObject::MapObject(TiXmlElement* node, string name)
{
	this->ReadXML(node, name);
}
MapObject::~MapObject()
{

}
void MapObject::ReadXML(TiXmlElement* node, string name)
{

}