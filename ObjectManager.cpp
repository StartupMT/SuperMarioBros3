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
	viewport = new Viewport(0, 0);
	//Mario bắt đầu 
	mario = Mario::GetInstance();
	mario->Init();
	mario->SetPosition(D3DXVECTOR2(300, 254));

	posView = viewport->GetPosition();
}

//Update Game
void ObjectManager::Update(float gameTime, Keyboard* key)
{
	//Kiểm tra va chạm xong mới update
	mario->Update(gameTime, key);

	//Update Viewport theo vị trí Mario
	D3DXVECTOR2 posMario = mario->GetPosition();
	viewport->Update(gameTime, key, posMario);
	//Kiểm tra xem có rơi ra Scene không
	if (posMario != mario->GetPosition())
	{
		mario->SetPosition(posMario);
	}
}

//Vẽ
void ObjectManager::Render()
{
	//Vẽ map
	map->Render(viewport);
	mario->Render(viewport);
}