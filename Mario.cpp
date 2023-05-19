﻿#include "Mario.h"
#include "GameDefine.h"
#include <math.h>

Mario* Mario::_mario = nullptr;
Mario::Mario()
{
}

Mario* Mario::GetInstance()
{
	if (nullptr == _mario) {
		_mario = new Mario();
	}
	return _mario;
}

Mario::~Mario()
{
	delete _marioController;
	delete _marioCollision;
	delete _mario;
}

void Mario::Init()
{
	//Tạo Animation
	Animation::DataAnimMap data;
	//Small
	data[Mario::Small + Object::Standing] = { 19, 19 };
	data[Mario::Small + Object::Running] = { 2,	3 };
	data[Mario::Small + Object::Running + 1] = { 2, 3, 5 };	//Chạy nhanh
	data[Mario::Small + Object::Running + 2] = { 6, 7, 1 };	//Trượt
	data[Mario::Small + Object::Running + 3] = { 4, 4 };	//Thắng
	data[Mario::Small + Object::Jumping] = { 5, 5 };
	data[Mario::Small + Object::Jumping + 1] = { 8, 8 };	//Anim chạy nhanh
	//Big
	data[Mario::Big + Object::Standing] = { 47, 47 };
	data[Mario::Big + Object::Running] = { 26,	27 };
	data[Mario::Big + Object::Running + 1] = { 2, 3, 5 };	//Chạy nhanh
	data[Mario::Big + Object::Running + 2] = { 6, 7, 1 };	//Trượt
	data[Mario::Big + Object::Running + 3] = { 28, 28 };	//Thắng
	data[Mario::Big + Object::Jumping] = { 5, 5 };
	data[Mario::Big + Object::Jumping + 1] = { 8, 8 };	//Anim chạy nhanh
	//Raccoon
	data[Mario::Raccoon + Object::Standing] = { 130, 130 };
	data[Mario::Raccoon + Object::Running] = { 2,	3 };
	data[Mario::Raccoon + Object::Running + 1] = { 2, 3, 5 };	//Chạy nhanh
	data[Mario::Raccoon + Object::Running + 2] = { 6, 7, 1 };	//Trượt
	data[Mario::Raccoon + Object::Running + 3] = { 4, 4 };	//Thắng
	data[Mario::Raccoon + Object::Jumping] = { 5, 5 };
	data[Mario::Raccoon + Object::Jumping + 1] = { 8, 8 };	//Anim chạy nhanh

	data[Mario::Small + Object::Standing] = { 19 , 19 };

	//_anim = new Animation(EnemyXML, EnemyPNG);
	//_anim = new Animation(MiscXML, MiscPNG);
	_anim = new Animation(MarioXML, MarioPNG);

	_anim->SetDataAnimation(data);

	//Tạo class xử lý va chạm
	_marioController = new MarioController();
	_marioCollision = new MarioCollision();

	AllowDraw = true;
	Tag = Object::Player;
	_marioType = Mario::Small;
	this->SetBound(15, 15);
	position = D3DXVECTOR2(0, 0);
	velocity = D3DXVECTOR2(0, 0);
	SetState(Object::Standing);
	HP = 1;
}

void Mario::BeforeUpdate(float gameTime, Keyboard* key)
{
	this->SetBound(Width, Height);

	//Check handler controller
	_marioController->Update(gameTime, key);
}

D3DXVECTOR2 Mario::OnCollision(Object* obj, D3DXVECTOR2 side)
{
	_marioCollision->_obj = obj;
	_marioCollision->_side = side;
	//Check mario collision by state
	_marioCollision->PlayCollisionF();
	return side;
}

void Mario::Update(float gameTime, Keyboard* key)
{
	//Update Animation
	UpdateAnimation();
	_anim->Update(gameTime);

	Object::Update(gameTime, key);
}

void Mario::UpdateAnimation()
{
	int _state = 0;
	if (State == Object::Running)
	{
		_state = _marioController->isBake ? 3 : abs(velocity.x) >= MaxSpeed ? 2 : abs(velocity.x) >= MaxRun ? 1 : 0;
		State = velocity.x == 0 ? Object::Standing : State;
	}
	else if (State == Object::Jumping)
		_state = _marioController->isSpeedJump;

	_anim->NewAnimationByIndex(_marioType + this->State + _state);
	this->SetBound(Width, Height);
	_anim->SetPosition(D3DXVECTOR2(position.x, position.y + Height / 2));
	_anim->SetFlipFlag(FlipFlag);
}

void Mario::ChangeMarioType(MarioType marioType)
{
	//_marioType = marioType;
	//if (key->IsKeyDown(DIK_A))
	//{
	//	this->SetBound(15, 15);
	//}
	//if (key->IsKeyDown(DIK_S))
	//{
	//	mario->_marioType = Mario::Big;
	//	mario->SetBound(17, 25);
	//}
	//if (key->IsKeyDown(DIK_D))
	//{
	//	mario->_marioType = Mario::Raccoon;
	//	mario->SetBound(17, 25);
	//}
}

void Mario::SetBound(float width, float height)
{
	//InfoSprite::Infoframe info = _anim->GetCurrentFrameInfo();
	Width = width;
	Height = height;
	bound.left = position.x - Width / 2;
	bound.right = bound.left + Width;
	bound.top = position.y + Height;
	bound.bottom = position.y;
}

void Mario::Render(Viewport* viewport)
{
	//Vẽ Mario
	if (AllowDraw)
	{
		_anim->Render(viewport);
	}
	DrawLine::GetInstance()->DrawRect(bound);
}
