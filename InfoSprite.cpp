#include "InfoSprite.h"



InfoSprite::InfoSprite(const char* path)
{
	ReadXML(path);
}

InfoSprite::~InfoSprite()
{
}


void  InfoSprite::ReadXML(const char* path)
{
	//Lấy tài liệu xml
	TiXmlDocument doc(path);
	if (!doc.LoadFile())
	{
		MessageBox(NULL, "Can't load Sprite xml file", "Error", MB_OK);
		return;
	}
	//Lấy thông tin thẻ
	TiXmlElement* sprite = doc.RootElement();
	TiXmlElement* indexml = nullptr;
	//Lấy thông tin kích thước sprite
	sprite->QueryFloatAttribute("width", &this->Width);
	sprite->QueryFloatAttribute("height", &this->Height);
	//Lấy kích thích frame mặc định
	sprite->QueryFloatAttribute("framew", &this->frameW);
	sprite->QueryFloatAttribute("frameh", &this->frameH);
	//Lấy thông tin từng index
	sprite->QueryIntAttribute("frame", &this->Frame);
	int n;
	for (indexml = sprite->FirstChildElement(); indexml != NULL; indexml = indexml->NextSiblingElement())
	{
		indexml->QueryIntAttribute("n", &n);
		indexml->QueryFloatAttribute("x", &this->InfoFrame[n].x);
		indexml->QueryFloatAttribute("y", &this->InfoFrame[n].y);
		indexml->QueryFloatAttribute("w", &this->InfoFrame[n].w);
		indexml->QueryFloatAttribute("h", &this->InfoFrame[n].h);
	}
}

float InfoSprite::GetWidth()
{
	return this->Width;
}

float InfoSprite::GetHeight()
{
	return this->Height;
}

float InfoSprite::GetFrameWidth()
{
	return this->frameW;
}

float InfoSprite::GetFrameHeight()
{
	return this->frameH;
}

RECT InfoSprite::GetRect(int Index)
{
	RECT rect;
	rect.left = InfoFrame[Index].x;	//x = IndexInfo[Index][0];
	rect.top = InfoFrame[Index].y;		//y = IndexInfo[Index][1];
	rect.right = rect.left + InfoFrame[Index].w;
	rect.bottom = rect.top + InfoFrame[Index].h;
	return rect;
}