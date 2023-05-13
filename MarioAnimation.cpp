#include "MarioAnimation.h"
#include "Mario.h"

MarioAnimation::MarioAnimation(InfoSprite* info):Animation(info)
{
	//Animation functions
	_functionMap[Object::Standing] = &MarioAnimation::Stand;
	_functionMap[Object::Moving] = &MarioAnimation::Move;
	Stand();
}

MarioAnimation::MarioAnimation()
{
}

MarioAnimation::~MarioAnimation()
{
}

//Đứng im
void MarioAnimation::Stand()
{
	delay = 50;
	start = 1; end = 3;
}

//Di chuyển
void MarioAnimation::Move()
{
	delay = RunDelay;
	start = 2; end = 3;
}

void MarioAnimation::Update(float gameTime, Keyboard* key)
{
	Object* mario = Mario::GetInstance();
	if (mario->State != mario->oldState)
	{
		//Lấy Function từ mario state
		FunctionMap::iterator it = _functionMap.find(mario->State);
		//(it->second) là con trỏ hàm = &Stand
		(this->*(it->second))();	//	(this->*(it->second)) = this->Stand
	}

	//Update Animation
	Animation::Update(gameTime, key);
	timechange += gameTime;
}
