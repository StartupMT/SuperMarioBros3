#include "MarioController.h"
#include "Mario.h"

MarioController::MarioController()
{
	mario = Mario::GetInstance();
	mario->SetState(Object::Standing);
	isAllowJump = false;
	isFall = true;
	isAllowAttack = false;
	isAllowFly = false;
	timeAttack = 0.0f;

	_functionMap[Object::Standing] = &MarioController::StandState;
	_functionMap[Object::Running] = &MarioController::RunState;
	_functionMap[Object::Jumping] = &MarioController::JumpState;
	_functionMap[Object::Jumping] = &MarioController::AttackState;
}

MarioController::~MarioController()
{
}

//Rơi
void MarioController::Fall()
{
	mario->SetVelocityY(-Gravity);
}

//Trạng thái Đứng
void MarioController::StandState()
{
	isAllowJump = true;//Cho nhảy khi đứng hoặc chạy
	isFall = false;//cho nhảy thì không rơi
	mario->SetVelocity(0, 0);
	if (key->IsKeyDown(Dik_JUMP))
	{
		mario->SetState(Object::Jumping);
	}
	else if (key->IsKeyDown(Dik_LEFT) || key->IsKeyDown(Dik_RIGHT))
	{
		mario->SetState(Object::Running);
	}
	else if (key->IsKeyDown(Dik_DOWN))
	{
		mario->SetState(Object::Sitting);
	}
	else if (key->IsKeyDown(Dik_ATTACK))
	{
		mario->SetState(Object::Attacking);
	}
	else
	{
		mario->SetState(Object::Standing);
	}
}

//Trang thái chạy
void MarioController::RunState()
{
	isAllowJump = true;
	isAllowFly = false;
	isFall = false;

	if (key->IsKeyDown(Dik_LEFT) || key->IsKeyDown(Dik_RIGHT))
	{
		MoveX();
		if (key->IsKeyDown(Dik_JUMP))
		{
			mario->SetState(Object::Jumping);
		}
		else if (key->IsKeyDown(Dik_ATTACK))
		{
			mario->SetState(Object::Attacking);
		}
		else
		{
			//isFall = true;
			//Fall();
			//mario->SetState(Object::Running);
			//if (mario->GetVelocity().y < -FallAc)
			//{
			//	isAllowJump = false;
			//	mario->SetVelocity(mario->GetVelocity().x, -Gravity);
			//	mario->SetState(Object::Jumping);
			//}
		}
	}
	else mario->SetState(Object::Standing);
}

void MarioController::MoveX()
{
	if (key->IsKeyDown(Dik_RIGHT))
	{
		mario->SetVelocityX(RunSpeed);
		mario->SetFlipFlag(false);
	}
	else if (key->IsKeyDown(Dik_LEFT))
	{
		mario->SetVelocityX(-RunSpeed);
		mario->SetFlipFlag(true);
	}
	else
	{
		mario->SetVelocityX(0);
	}
}

//Trạng thái nhảy
void MarioController::JumpState()
{
	if (isAllowJump)
	{
		posStartJump = mario->GetPosition().y;
		mario->SetVelocityY(JumpSpeed);
	}
	isAllowJump = false;

	if (key->GIsKeyUp(Dik_JUMP) || (mario->GetPosition().y - posStartJump) >= JumpMax)
		isFall = true;

	if (isFall && mario->GetVelocity().y == 0.0f)
	{
		mario->SetState(Object::Standing);
	}
	else
	{
		if (key->IsKeyDown(Dik_ATTACK))
		{
			mario->SetState(Object::Attacking);
		}
		else
		{
			Fall();
			mario->SetState(Object::Jumping);
		}
	}
}

//Trạng thái đánh
void MarioController::AttackState()
{
	if (isAllowAttack)
	{
		mario->SetVelocity(0, 0);
		mario->SetState(Object::Attacking);
	}
}

//Trạng thái chêt
void MarioController::DeadState()
{
	mario->SetVelocity(0, 0);
	mario->SetState(Object::Dying);
}

void MarioController::PlayControllerF(Keyboard* key)
{
	this->key = key;
	//Lấy Function từ mario state
	FunctionMap::iterator it = _functionMap.find(mario->State);
	(this->*(it->second))();
}