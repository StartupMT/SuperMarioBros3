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
	_functionMap[Object::Attacking] = &MarioController::AttackState;
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
	mario->SetVelocityY(-Gravity);
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
	mario->SetVelocityY(-Gravity);
	if (key->IsKeyDown(Dik_LEFT) || key->IsKeyDown(Dik_RIGHT))
	{
		if (key->IsKeyDown(Dik_JUMP))
		{
			mario->SetState(Object::Jumping);
		}
		if (key->IsKeyDown(Dik_ATTACK))
		{
			if (timeAc > MaxTimeAcc)
				isCount = true;
		}
	}
	else
	{
		if (mario->GetVelocity().x == 0)
			mario->SetState(Object::Standing);
	}
}

void MarioController::MoveX()
{
	float speed = mario->GetVelocity().x;
	float speedRun = key->IsKeyDown(Dik_ATTACK) ? MaxRun : RunSpeed;
	speedRun = accCount >= MaxSpeedCount ? MaxSpeed : speedRun;
	isBake = false;
	if (key->IsKeyDown(Dik_RIGHT))
	{
		isBake = speed < 0;
		speed = speed < RunSpeed ? speed + accDown : speedRun;
		mario->SetFlipFlag(false);
	}
	else if (key->IsKeyDown(Dik_LEFT))
	{
		isBake = speed > 0;
		speed = speed > -RunSpeed ? speed - accDown : -speedRun;
		mario->SetFlipFlag(true);
	}
	else
	{
		if (speed > 0)
		{
			speed = speed - accDown;
			speed = speed < 0 ? 0 : speed;
		}
		else
		{
			speed = speed + accDown;
			speed = speed > 0 ? 0 : speed;
		}
	}
	mario->SetVelocityX(speed);
}

//Trạng thái nhảy
void MarioController::JumpState()
{
	if (isAllowJump)
	{
		isSpeedJump = accCount >= MaxSpeedCount;
		posStartJump = mario->GetPosition().y;
		mario->SetVelocityY(JumpSpeed);
	}
	isAllowJump = false;

	if (key->GIsKeyUp(Dik_JUMP) || (mario->GetPosition().y - posStartJump) >= MaxJump)
		isFall = true;

	if (isFall && mario->GetVelocity().y == 0.0f)
	{
		mario->SetState(Object::Standing);
	}
	else
	{
		Fall();
		mario->SetState(Object::Jumping);
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

void MarioController::PlayControllerF()
{
	//Lấy Function từ mario state
	FunctionMap::iterator it = _functionMap.find(mario->State);
	(this->*(it->second))();
}

void MarioController::Update(float gameTime, Keyboard* key)
{
	this->key = key;
	isCount = false;

	if (key->IsKeyDown(DIK_A))
	{
		mario->SetBound(15, 15);
		mario->_marioType = Mario::Small;
	}
	if (key->IsKeyDown(DIK_S))
	{
		mario->_marioType = Mario::Big;
		mario->SetBound(17, 25);
	}
	if (key->IsKeyDown(DIK_D))
	{
		mario->_marioType = Mario::Raccoon;
		mario->SetBound(17, 25);
	}

	this->PlayControllerF();

	//CheckTime
	if (timeAttack > 0.5)
		isAllowAttack = true;
	else
	{
		timeAttack += gameTime;
		isAllowAttack = false;
	}


	//Check acceleration
	MoveX();
	if (timeAc > MaxTimeAcc)
	{
		accDown = SlowDown;
		if (isCount && !isBake)
			accCount++;
		else
			accCount--;
		//Giảm tốc độ khi thắng hoặc thả phím tấn công
		accCount = ((isBake || key->GIsKeyUp(Dik_ATTACK)) && accCount > MaxSpeedCount) ? MaxSpeedCount - 10 : accCount;
		accCount = accCount < 0 ? 0 : (accCount > MaxSpeedCount && isCount) ? MaxSpeedCount * 1.3 : accCount;

		timeAc = 0.0f;
	}
	else
	{
		accDown = 0;
		timeAc += gameTime;
	}
}