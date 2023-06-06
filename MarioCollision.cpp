#include "MarioCollision.h"
#include "Mario.h"

MarioCollision::MarioCollision()
{
	mario = Mario::GetInstance();
	_functionMap[Object::Standing] = &MarioCollision::StandCollision;
	_functionMap[Object::Running] = &MarioCollision::RunCollision;
	_functionMap[Object::Jumping] = &MarioCollision::JumpCollision;
	_functionMap[Object::Attacking] = &MarioCollision::AttackCollision;
	_functionMap[Object::Dying] = &MarioCollision::DeadCollision;
}

MarioCollision::~MarioCollision()
{
}

void MarioCollision::OnCollision()
{
	//Check mario collision by state
	PlayCollisionF();
	//Kiểm tra mario rơi
	isGround = isGround || _side.y == Collision::BOTTOM;
	isCollisionTop = isCollisionTop || _side.y == Collision::TOP;
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
	mario->State = Object::Standing;
}

//Va chạm khi chạy
void MarioCollision::RunCollision()
{
	if (_side.x == Collision::RIGHT)
	{
		mario->State = Object::Standing;
	}
}

//va chạm khi nhảy
void MarioCollision::JumpCollision()
{
	if (!mario->_marioController->isFall)
		return;

	if (_side.y == Collision::BOTTOM)
	{
		mario->State = Object::Standing;
		if (_obj->Tag == Object::Enemy)
		{
			_obj->State = Object::Dying;
			mario->_marioController->ShortJump();
		}
	}
}

//va chạm khi nhảy
void MarioCollision::AttackCollision()
{

}

//va chạm khi nhảy
void MarioCollision::DeadCollision()
{

}