#include "ObjectManager.h"
#include "string.h"
#pragma warning(disable : 4996)


ObjectManager* ObjectManager::_objectManager;

ObjectManager* ObjectManager::GetInstance()
{
	if (nullptr == _objectManager) {
		_objectManager = new ObjectManager();
	}
	return _objectManager;
}

ObjectManager::ObjectManager()
{
	viewport = new Viewport(0, 0);
}
ObjectManager::~ObjectManager()
{
	delete map;
	delete viewport;
	delete mario;
}

//Load Data Game
void ObjectManager::InitDT()
{
	//load Objecct
	map = new Map();
	//Mario bắt đầu 
	mario = Mario::GetInstance();
	mario->Init();
	mario->SetPosition(D3DXVECTOR2(300, 254));

	//Enemy
	Enemy* enemy = new Enemy();
	enemy->Init(D3DXVECTOR2(300, 250));

	map->ListObject.push_back(mario);
	map->ListObject.push_back(enemy);

	posView = viewport->GetPosition();
}

//Update Game
void ObjectManager::Update(float gameTime, Keyboard* key)
{
	mario->BeforeUpdate(gameTime, key);
	//Check Collision
	for (size_t i = 0; i < map->ListObject.size(); i++)
		for (size_t j = 0; j < map->ListObject.size(); j++)
			if (i != j)
				map->ListObject.at(i)->OnCollision(map->ListObject.at(j), gameTime);

	//Update all Object
	for (size_t i = 0; i < map->ListObject.size(); i++)
		map->ListObject.at(i)->Update(gameTime, key);

	//Update Viewport theo vị trí Mario
	D3DXVECTOR2 posMario = mario->GetPosition();
	viewport->Update(gameTime, key, posMario);
	//Kiểm tra xem có rơi ra Scene không
	if (posMario != mario->GetPosition())
	{
		mario->SetPosition(posMario);
	}
}

Viewport* ObjectManager::GetViewPort()
{
	return viewport;
}

//Vẽ
void ObjectManager::Render()
{
	//Vẽ map
	map->Render(viewport);
	//Vẽ
	for (size_t i = 0; i < map->ListObject.size(); i++)
		map->ListObject.at(i)->Render(viewport);

	//GUI
	GUI::GetInstance()->Render();

}