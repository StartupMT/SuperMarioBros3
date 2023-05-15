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
protected:
	MarioController* _marioController;
	MarioCollision* _marioCollision;
	const char* pathPNG;
public:
	Mario(); 
	~Mario();

	void Init();
	void BeforeUpdate(float gameTime, Keyboard* key);
	void Update(float gameTime, Keyboard* key);
	void UpdateAnimation(float gameTime);
	void SetTexture(char* path);
	void SetBound(float width, float height);
	void Render(Viewport* viewport);
	static Mario* GetInstance();
};
