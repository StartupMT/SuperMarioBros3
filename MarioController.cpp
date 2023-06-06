﻿#include "MarioController.h"
#include "Mario.h"

MarioController::MarioController()
{
	mario = Mario::GetInstance();
	mario->SetState(Object::Standing);
	isAllowJump = false;
	isFall = true;
	isAllowAttack = false;
	timeAttack = 0.0f;

	_functionMap[Object::Standing] = &MarioController::StandState;
	_functionMap[Object::Running] = &MarioController::RunState;
	_functionMap[Object::Jumping] = &MarioController::JumpState;
	_functionMap[Object::Attacking] = &MarioController::AttackState;
	_functionMap[Object::Dying] = &MarioController::DeadState;

}

MarioController::~MarioController()
{
}

//Trạng thái Đứng
void MarioController::StandState() //reset all state
{
	timeFlyDown = 0;
	isFly = false;
	isShortJump = false;
	isAllowJump = true;//Cho nhảy khi đứng hoặc chạy
	isFall = false;//cho nhảy thì không rơi
	mario->SetVelocityY(Gravity);
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
	isShortJump = false;
	isAllowJump = true;
	isFall = false;
	mario->SetVelocityY(Gravity);
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
}

void MarioController::MoveX()
{
	float speed = mario->GetVelocity().x;
	float speedRun = key->IsKeyDown(Dik_ATTACK) ? MaxRun : RunSpeed;
	speedRun = isSpeed ? MaxSpeed : speedRun;
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

void MarioController::ShortJump()
{
	StandState();
	isShortJump = true;
	mario->SetState(Object::Jumping);
}

void MarioController::Fall()
{
	mario->SetState(Object::Jumping);
	isAllowJump = false;
	isFall = true;
}

//Trạng thái nhảy
void MarioController::JumpState()
{
	if (isAllowJump)
	{
		isSpeedJump = isSpeed;
		posYStartJump = mario->GetPosition().y;
		maxJump = isShortJump ? MaxEnemyJump : isFly ? 0 : MaxJump;
		isFall = false;
	}

	isAllowJump = false;
	isCount = isSpeedJump; //đếm tăng tốc
	float jumpSpeed = isSpeedJump ? JumpSpeed * 1.2 : JumpSpeed; // nếu mà chạy nhanh thì nhảy cao hơn xí

	//Fall
	if (!isFall && ((key->GIsKeyUp(Dik_JUMP) && maxJump >= MaxJump) || (mario->GetPosition().y - posYStartJump) >= maxJump))
	{
		isFall = true;
		velYStartFall = jumpSpeed;
	}

	if (isFall)
	{
		isFallDown = velYStartFall < -0.5;//rơi tự do
		float gravity = Gravity;

		//Check Fly
		if (isFallDown && mario->_marioType == Mario::Raccoon)
		{
			isCount = false; //rơi khi là chồn không giữ speed
			if (key->GIsKeyDown(Dik_JUMP))
			{
				if (isSpeed)
					ShortJump();
				else if (timeFlyDown >= 0)
					timeFlyDown = 3;

				isFly = true;
			}
			//Nếu bay không đủ tốc độ thì rơi chậm
			if (timeFlyDown > 0)
			{
				gravity = gravity / 3;
				timeFlyDown -= fallAc;
			}
			else
			{
				timeFlyDown = 0;
				isFly = isSpeed && isFly;
			}
		}
		else isFly = false;

		velYStartFall -= fallAc; //trừ vận tốc sẽ nhảy nhẹ 1 đoạn
		velYStartFall = isFallDown ? gravity : velYStartFall;

		mario->SetVelocityY(velYStartFall);
		return;
	}

	//JumpUP
	mario->SetVelocityY(jumpSpeed);
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
	//Giảm tốc độ khi thắng hoặc thả phím tấn công
	accCount = ((isBake || key->GIsKeyUp(Dik_ATTACK)) && accCount > MaxSpeedCount) ? MaxSpeedCount - 10 : accCount;
	if (timeAc > MaxTimeAcc)
	{
		fallAc = FallAc;
		accDown = SlowDown;
		if (isCount && !isBake)
			accCount++;
		else
			accCount--;
		accCount = accCount < 0 ? 0 : (accCount > MaxSpeedCount && isCount) ? MaxSpeedCount * 1.3 : accCount;

		timeAc = 0.0f;
	}
	else
	{
		accDown = 0;
		fallAc = 0;
		timeAc += gameTime;
	}
	isSpeed = accCount >= MaxSpeedCount;
}