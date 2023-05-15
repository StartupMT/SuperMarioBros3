#pragma once
#include "DrawString.h"
#include "Graphic.h"
#include "Mario.h"

class GUI
{
protected:
	DrawString* gui;
	RECT rSpeed;
	char txtSpeed[10];
public:
	GUI();
	~GUI();
	void Render();
};

