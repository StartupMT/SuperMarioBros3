#include "MarioCollision.h"
#include "Mario.h"

MarioCollision::MarioCollision()
{
	mario = Mario::GetInstance();
	_functionMap[Object::Standing] = &MarioCollision::StandCollision;
	_functionMap[Object::Running] = &MarioCollision::RunCollision;
	_functionMap[Object::Jumping] = &MarioCollision::JumpCollision;
}

MarioCollision::~MarioCollision()
{
}

void MarioCollision::OnCollision()
{

}

//Chạy function ứng với state mario
void MarioCollision::PlayCollisionF()
{
	//Lấy Function từ mario state
	FunctionMap::iterator it = _functionMap.find(mario->State);
	//(it->second) là con trỏ hàm lấy từ <map> = &StandCollision
	(this->*(it->second))();	//	(this->*(it->second)) = this->StandCollision
}

//Va chạm khi đứng
void MarioCollision::StandCollision()
{

}

//Va chạm khi chạy
void MarioCollision::RunCollision()
{

}

//va chạm khi nhảy
void MarioCollision::JumpCollision()
{

}