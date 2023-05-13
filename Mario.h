#pragma once
#include "Object.h"
#include "MarioCollision.h"
#include "GameDefine.h"

using namespace Define;

class Mario : public Object
{
private:
	static Mario* _mario;
protected:
	MarioCollision* _marioCollision;
	const char* pathPNG;
public:
	Mario(); 
	~Mario();

	void Init();
	void Update(float gameTime, Keyboard* key);
	void UpdateAnimation(float gameTime);
	void Render(Viewport* viewport);
	void SetTexture(char* path);
	static Mario* GetInstance();
};

