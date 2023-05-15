#pragma once
#include "Graphic.h"
#include "Keyboard.h"
#include "GUI.h"
#include "Map.h"
#include "Mario.h"
#include "Viewport.h"
#include "Collision.h"
#include <vector>
#include "GameDefine.h"
#include "Wall.h"

using namespace Define;

class ObjectManager
{
private:
	static ObjectManager* _objectManager;
protected:
	vector <Object*> _listObject;

	Viewport* viewport;
	Mario* mario;
	Map* map;

	GUI* gui;
	D3DXVECTOR2 posView;
public:
	ObjectManager();
	~ObjectManager();

	static ObjectManager* GetInstance();
	//Load Data Game
	void InitDT();

	void Update(float gameTime, Keyboard* key);

	Viewport* GetViewPort();
	//Vẽ Object lên màn hình
	void Render();
};
