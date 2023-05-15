#include "GUI.h"
#include "string.h"
#pragma warning(disable : 4996)

GUI::GUI()
{
	//Text
	gui = new DrawString(Graphic::GetInstance(), 12);
	//Hiển thị Speed
	rSpeed = { 5, 200, 40, 235 };
}

GUI::~GUI()
{
	delete gui;
}

//Vẽ
void GUI::Render()
{
	//Hiển thị Score
	char speed[5];
	itoa(Mario::GetInstance()->_marioController->accCount, speed, 10);
	gui->Render(speed, rSpeed, D3DCOLOR_XRGB(255, 255, 255));
}