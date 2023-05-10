#pragma once
#include "Graphic.h"
#include "Keyboard.h"
#include "ObjectManager.h"
#include "GameDefine.h"

using namespace Define;

class SceneManager
{
	static SceneManager* _sceneManager;
public:
	SceneManager();
	~SceneManager();

	//Load Data Game
	void InitDT(Graphic* graphic);

	//Update Game sau khoảng thời gian gameTime
	void Update(float gameTime, Keyboard* key);
	//Vẽ Object lên màn hình
	void Render();
	static SceneManager* GetInstance();
};

