﻿#pragma once
#include "Graphic.h"
#include "Keyboard.h"
#include "Viewport.h"
#include "Collision.h"
#include "GameDefine.h"

using namespace Define;

class ObjectManager
{
private:
	static ObjectManager* _objectManager;
protected:
	Viewport* viewport;


	vector <RECT> listScene;
	D3DXVECTOR2 posView;
public:
	ObjectManager();
	~ObjectManager();

	static ObjectManager* GetInstance();
	//Load Data Game
	void InitDT(Graphic* graphic);
	void Update(float gameTime, Keyboard* key);
	//Vẽ Object lên màn hình
	void Render();
};

