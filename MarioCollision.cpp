#include "MarioCollision.h"
#include "Mario.h"
#include "map.h"

MarioCollision::MarioCollision()
{
	mario = Mario::GetInstance();
	_functionMap[Object::Standing] = &MarioCollision::StandCollision;
	_functionMap[Object::Running] = &MarioCollision::RunCollision;
	_functionMap[Object::Jumping] = &MarioCollision::JumpCollision;
	_functionMap[Object::Attacking] = &MarioCollision::StandCollision;
	_functionMap[Object::Dying] = &MarioCollision::DeadCollision;
}

MarioCollision::~MarioCollision()
{
}

void MarioCollision::OnCollision()
{
	//Check mario collision by state
	PlayCollisionF();

	//CheckAllState
	switch (_obj->Tag)
	{
	case Object::Enemy:
		CheckCollisionEnemy();
		_side = D3DXVECTOR2(Collision::NONE, Collision::NONE);
		break;
	case Object::Item:
		CheckCollisionItem();
		_side = D3DXVECTOR2(Collision::NONE, Collision::NONE);
		break;
	default:

		break;
	}

	//Kiểm tra mario rơi
	isGround = isGround || _side.y == Collision::BOTTOM;
	isCollisionTop = isCollisionTop || _side.y == Collision::TOP;
}

void MarioCollision::CheckCollisionEnemy()
{
	if (mario->_marioType - Mario::Small < Mario::Small)
	{
		mario->State = Object::Dying;
		mario->_marioController->velYStartFall = JumpSpeed;
	}
	else
		mario->_marioType = (Mario::MarioType)(mario->_marioType - Mario::Small);
}

//Va chạm với Item
void MarioCollision::CheckCollisionItem()
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
		mario->_marioController->StandState();
		if (_obj->Tag == Object::Enemy)
		{
			_obj->State = Object::Dying;
			mario->_marioController->ShortJump();
		}
	}
}

//kiểm tra va chạm khi tấn công
void MarioCollision::AttackCollision(Object* obj)
{
	RECT marioBound = mario->GetBound();
	RECT rectAttack{
		marioBound.left - 10,
		marioBound.top - 12,
		marioBound.right + 10,
		marioBound.bottom
	};
	if (Collision::isCollision(rectAttack, obj->GetBound()))
	{
		obj->State = Object::Dying;
	}
}

//va chạm khi nhảy
void MarioCollision::DeadCollision()
{

}