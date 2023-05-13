#pragma once
#include <d3dx9.h>
#include "TinyXML\tinyxml.h"
class InfoSprite
{
protected:
	float Width, Height ,frameW , frameH;
	int Frame;
	struct Infoframe
	{
		float x;
		float y;
		float w;
		float h;
	};
	Infoframe InfoFrame[85];
public:
	InfoSprite(const char* path);
	~InfoSprite();

	float GetWidth();
	float GetHeight();
	float GetFrameWidth();
	float GetFrameHeight();

	void ReadXML(const char* path);
	RECT GetRect(int Index);
};

