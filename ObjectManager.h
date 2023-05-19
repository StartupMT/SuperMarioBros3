#pragma once
#include <vector>
#include "Graphic.h"
#include "Keyboard.h"
#include "GUI.h"
#include "Viewport.h"
#include "Collision.h"
#include "Map.h"
#include "Mario.h"
#include "Wall.h"
#include "Enemy.h"

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
