#pragma once
#include "Graphic.h"
#include "Keyboard.h"
#include "Map.h"
#include "Mario.h"
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
	Mario* mario;
	Map* map;

	vector <RECT> listScene;
	D3DXVECTOR2 posView;

	Sprite* sprite_mario;
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
