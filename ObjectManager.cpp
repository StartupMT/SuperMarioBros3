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
	delete viewport;
}

//Load Data Game
void ObjectManager::InitDT(Graphic* graphic)
{
	

	posView = viewport->GetPosition();
}

//Update Game
void ObjectManager::Update(float gameTime, Keyboard* key)
{
	
}

//Vẽ
void ObjectManager::Render()
{

}