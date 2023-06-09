﻿#include "Enemy.h"
#include "Mario.h"

Animation* Enemy::GetAnimationEnemy()
{
	//Tạo Animation
	Animation::DataAnimMap data;
	// Goomba
	data[Enemy::Goomba + Object::Standing] = { 0 , 0 };
	data[Enemy::Goomba + Object::Running] = { 1 , 2 };
	data[Enemy::Goomba + Object::Dying] = { 3 , 3 };
	// Red Goomba
	data[Enemy::Goomba + Object::Standing + 1] = { 4 , 5 }; // =idle
	data[Enemy::Goomba + Object::Running + 1] = { 6 , 7 }; // =walk 
	data[Enemy::Goomba + Object::Jumping + 1] = { 6 , 7 }; // =walk 
	data[Enemy::Goomba + Object::Dying + 1] = { 8 , 8 }; // =die

	// Red koopa
	data[Enemy::Koopa + Object::Standing] = { 26 , 27 };
	data[Enemy::Koopa + Object::Running] = { 26 , 27 };
	data[Enemy::Shell + Object::Standing] = { 30 , 30 }; // = ( shell red)
	data[Enemy::Shell + Object::Running] = { 30 , 31 }; // 

	// Green koopa
	data[Enemy::Koopa + Object::Standing + 1] = { 32 , 33 };
	data[Enemy::Koopa + Object::Running + 1] = { 32 , 33 };
	data[Enemy::Koopa + Object::Jumping + 1] = { 38 , 40 };
	data[Enemy::Shell + Object::Standing + 1] = { 35 , 35 }; // = ( shell red)
	data[Enemy::Shell + Object::Running + 1] = { 36 , 37 }; //

	// Piranha Plant ( cái cây màu xanh cắn)
	data[Enemy::Plant + Object::Standing] = { 24 , 25 };

	//// Fire piranha plant ( cây bắn đạn)
	// Red
	data[Enemy::Plant + Object::Standing] = { 18 , 18 }; // headdown
	data[Enemy::Plant + Object::Running] = { 19 , 19 }; // headup
	// Greem
	data[Enemy::Plant + Object::Standing + 1] = { 20 , 20 }; // headdown
	data[Enemy::Plant + Object::Running + 1] = { 21 , 21 }; // headup
	// cây đỏ tấn công
	data[Enemy::Plant + Object::Standing + 2] = { 65 , 66 }; // down
	data[Enemy::Plant + Object::Running + 2] = { 67 , 68 }; // up
	// cây xanh tấn công
	data[Enemy::Plant + Object::Standing + 3] = { 70 , 71 }; // down
	data[Enemy::Plant + Object::Running + 3] = { 72 , 73 }; // up

	Animation* _animEnemy = new Animation(EnemyXML, EnemyPNG);
	_animEnemy->SetDataAnimation(data);
	return _animEnemy;
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
	delete _anim;
}

void Enemy::Init(D3DXVECTOR2 pos, int _type, int kind)
{
	AllowDraw = true;
	Tag = Object::Enemy;

	_anim = GetAnimationEnemy();
	_enemyType = (Enemytype)_type;
	_kind = kind;
	position = pos;
	velocity = D3DXVECTOR2(-EnemySpeed, Gravity);
	SetState(Object::Running);
	this->SetBound(15, 15);
	timeDead = 0;
	HP = 1;
}

void Enemy::Controller()
{
	velocity.y = Gravity;
}

D3DXVECTOR2 Enemy::OnCollision(Object* obj, D3DXVECTOR2 side)
{
	switch (obj->Tag)
	{
	case Object::Player:
		Mario::GetInstance()->_marioCollision->CheckCollisionEnemy();
		return D3DXVECTOR2(Collision::NONE, side.y);

	case Object::Block:
		if (side.x != Collision::NONE)
		{
			velocity.x = -velocity.x;
			side.x = Collision::NONE;
		}
		return side;

	default:
		return D3DXVECTOR2(Collision::NONE, Collision::NONE);
	}
}

void Enemy::OnCollision(Object* obj)
{
	if (obj->Tag == Object::Player)
		Mario::GetInstance()->_marioCollision->CheckCollisionEnemy();
}

void Enemy::BeforeUpdate(float gameTime, Keyboard* key)
{
	this->SetBound(Width, Height);
	this->Controller();
	if (State == Object::Jumping) JumpState();
}

void Enemy::Update(float gameTime, Keyboard* key)
{
	//Update Animation
	if (State == Object::Dying)
	{
		this->SetBound(0, 0);
		this->SetVelocity(0, 0);
		timeDead += gameTime;
		if (timeDead > 1)
			AllowDraw = false;
	}

	UpdateAnimation(gameTime);

	Object::Update(gameTime, key);
}

void Enemy::UpdateAnimation(float gameTime)
{
	_anim->NewAnimationByIndex(_enemyType + this->State + _kind);
	_anim->SetPosition(D3DXVECTOR2(position.x, position.y + Height / 2));
	_anim->SetFlipFlag(velocity.x > 0);
	_anim->Update(gameTime);
}

void Enemy::SetBound(float width, float height)
{
	InfoSprite::Infoframe info = _anim->GetCurrentFrameInfo();

	Width = info.w;
	Height = info.h;

	float w = width >= 0 ? width : Width;
	float h = height >= 0 ? height : Height;

	bound.left = position.x - w / 2;
	bound.right = bound.left + w;
	bound.top = position.y + h;
	bound.bottom = position.y;
}

void Enemy::Render(Viewport* viewport)
{
	//Vẽ Enemy
	if (AllowDraw)
	{
		_anim->Render(viewport);
	}
	DrawLine::GetInstance()->DrawRect(bound);
}