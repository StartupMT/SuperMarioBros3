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
	for (size_t i = 0; i < _listObject.size(); i++)
	{
		delete _listObject.at(i);
	}
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

	//Wall
	Wall* wall = new Wall();
	wall->Init(Wall::normal, D3DXVECTOR2(300, 200));
	wall->GetBound(3000, 10);

	Wall* wall1 = new Wall();
	wall1->Init(Wall::normal, D3DXVECTOR2(200, 250));
	wall1->GetBound(10, 100);

	Wall* wall2 = new Wall();
	wall2->Init(Wall::normal, D3DXVECTOR2(400, 250));
	wall2->GetBound(10, 100);

	//Enemy
	Enemy* enemy = new Enemy();
	enemy->Init(D3DXVECTOR2(300, 230));

	_listObject.push_back(mario);
	_listObject.push_back(wall);
	_listObject.push_back(wall1);
	_listObject.push_back(wall2);
	_listObject.push_back(enemy);

	posView = viewport->GetPosition();
}

//Update Game
void ObjectManager::Update(float gameTime, Keyboard* key)
{
	mario->BeforeUpdate(gameTime, key);
	//Check Collision
	for (size_t i = 0; i < _listObject.size(); i++)
		for (size_t j = 0; j < _listObject.size(); j++)
			if (i != j)
				_listObject.at(i)->OnCollision(_listObject.at(j), gameTime);

	//Update all Object
	for (size_t i = 0; i < _listObject.size(); i++)
		_listObject.at(i)->Update(gameTime, key);

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
	//map->Render(viewport);
	//Vẽ
	for (size_t i = 0; i < _listObject.size(); i++)
		_listObject.at(i)->Render(viewport);

	//GUI
	GUI::GetInstance()->Render();

}