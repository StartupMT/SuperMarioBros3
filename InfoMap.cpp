
#include"InfoMap.h"
#pragma warning(disable : 4996)

InfoMap::InfoMap(const char* path)
{
	this->ReadXMl(path);
}
InfoMap::~InfoMap()
{
}

void InfoMap::ReadXMl(const char* path)
{
	const char* dataText;
	TiXmlDocument doc(path);
	if (!doc.LoadFile())
	{
		MessageBox(NULL, "Can't load Map xml file", "Error", MB_OK);
		return;
	}
	TiXmlElement* root = doc.RootElement();
	root->QueryFloatAttribute("tilewidth", &tileWidth);
	root->QueryFloatAttribute("tileheight", &tileHeight);
	root->QueryIntAttribute("width", &width);
	root->QueryIntAttribute("height", &height);
	TiXmlElement* child1 = root->FirstChildElement();
	child1->QueryIntAttribute("tilecount", &tileCount);
	child1->QueryIntAttribute("columns", &tileColumns);
	TiXmlElement* child2 = child1->NextSiblingElement();
	layerName = (char*)child2->Attribute("name");
	TiXmlElement* child2_1 = child2->FirstChildElement();
	dataText = child2_1->GetText();
	char* token;
	token = strtok((char*)(dataText), ",");
	int row = height - 1;
	int column = 0;
	while (token != NULL)
	{
		data[row][column] = atoi(token);//Lưu mảng trong file xml vào đây
		column++;
		if (column >= width)
		{
			row--;
			column = 0;
		}
		token = strtok(NULL, ",");
	}
}


int InfoMap::GetData(D3DXVECTOR2 position)
{
	int w = position.x / tileWidth;
	int h = position.y / tileHeight;
	return data[h][w];
}
void InfoMap::SetData(D3DXVECTOR2 position, int Data)
{
	int w = position.x / tileWidth;
	int h = position.y / tileHeight;
	data[h][w] = Data;
}