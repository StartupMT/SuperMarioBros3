#pragma once
#include "Object.h"
#include "MarioCollision.h"
#include "MarioController.h"
#include "GameDefine.h"

using namespace Define;

class Mario : public Object
{
private:
	static Mario* _mario;
public:
	enum MarioType
	{
		Small = 100,
		Big = 200,
		Raccoon = 300,
	} _marioType;

	MarioController* _marioController;
	MarioCollision* _marioCollision;
	const char* pathPNG;
public:
	Mario(); 
	~Mario();

	void Init();
	void BeforeUpdate(float gameTime, Keyboard* key);
	void Update(float gameTime, Keyboard* key);
	void UpdateAnimation();
	void SetTexture(char* path);
	void ChangeMarioType(MarioType marioType);
	void SetBound(float width, float height);
	void Render(Viewport* viewport);
	static Mario* GetInstance();
};
