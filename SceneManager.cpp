#include "SceneManager.h"

SceneManager* SceneManager::_sceneManager;
SceneManager* SceneManager::GetInstance()
{
	if (nullptr == _sceneManager) {
		_sceneManager = new SceneManager();
	}
	return _sceneManager;
}

SceneManager::SceneManager()
{
}
SceneManager::~SceneManager()
{
}

//Load Data Game
void SceneManager::InitDT(Graphic* graphic)
{
	ObjectManager::GetInstance()->InitDT(graphic);
}

//Update các scene game Update lớn nhất
void SceneManager::Update(float gameTime, Keyboard* key)
{
	ObjectManager::GetInstance()->Update(gameTime, key);
}

//Vẽ Object lên màn hình
void SceneManager::Render()
{
	ObjectManager::GetInstance()->Render();
}