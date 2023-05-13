#pragma once
#include "Object.h"
#include "MarioAnimation.h"
#include "GameDefine.h"

using namespace Define;

class Mario : public Object
{
private:
	static Mario* _mario;
protected:
	MarioAnimation* _marioAnim;
public:
	Mario(); 
	~Mario();
	const char* pathPNG;

	InfoSprite* info_mario;

	void Init(Sprite* sprite_mario);
	void Update(float gameTime, Keyboard* key);
	void Render(Viewport* viewport);
	static Mario* GetInstance();
};

