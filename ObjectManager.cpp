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

	delete sprite_mario;
}

//Load Data Game
void ObjectManager::InitDT(Graphic* graphic)
{
	//load sprite
	sprite_mario = new Sprite(graphic, MarioPNG);
	viewport = new Viewport(0, 0);

	//load Objecct
	map = new Map(graphic);

	//Mario bắt đầu 
	mario = Mario::GetInstance();
	mario->Init(sprite_mario);
	mario->SetPosition(D3DXVECTOR2(300, 300));


	posView = viewport->GetPosition();
}

//Update Game
void ObjectManager::Update(float gameTime, Keyboard* key)
{
	mario->Update(gameTime, key);
	//Update Viewport theo vị trí Mario
	D3DXVECTOR2 posMario = mario->GetPosition();
	viewport->Update(gameTime, key, posMario);
}

//Vẽ
void ObjectManager::Render()
{
	map->Render(viewport);
	mario->Render(viewport);
}