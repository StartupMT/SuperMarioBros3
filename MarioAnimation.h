#pragma once
#include <d3dx9.h>
#include "Keyboard.h"
#include "Animation.h"
#include "Object.h"
#include "map"
#include "GameDefine.h"
using namespace Define;

class MarioAnimation :public Animation
{
protected:
	typedef void(MarioAnimation::*marioAnimationF)(void);
	typedef map<int, marioAnimationF> FunctionMap;
	FunctionMap _functionMap;

	D3DXVECTOR2 LocalGun;

	float change = 1.0f;
	float timechange = 0.0f;
public:
	MarioAnimation(InfoSprite* info);
	MarioAnimation();
	~MarioAnimation();

	void Stand();
	void Move(); //Di chuyển
	void Update(float gameTime, Keyboard* key);
};

