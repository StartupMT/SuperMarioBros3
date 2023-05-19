#include "Enemy.h"
#include "GUI.h"

Animation* Enemy::GetAnimationEnemy()
{
	//Tạo Animation
	Animation::DataAnimMap data;
	// Goomba
	data[Enemy::Goomba + Object::Standing] = { 0 , 0 };
	data[Enemy::Goomba + Object::Running] = { 1 , 2 };
	data[Enemy::Goomba + Object::Dying] = { 3 , 3 };

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

void Enemy::Init(D3DXVECTOR2 pos, int kind)
{
	AllowDraw = true;
	Tag = Object::Enemy;

	_anim = GetAnimationEnemy();
	_enemyType = Enemy::Goomba;
	_kind = kind;
	position = pos;
	velocity = D3DXVECTOR2(-EnemySpeed, Gravity);
	SetState(Object::Running);
	this->SetBound(14, 16);
	HP = 1;
}

void Enemy::EnemyController()
{
}

D3DXVECTOR2 Enemy::OnCollision(Object* obj, D3DXVECTOR2 side)
{
	switch (obj->Tag)
	{
	case Object::Player:
		obj->State = Object::Dying;
		return D3DXVECTOR2(Collision::NONE, Collision::NONE);

	default:
		if (side.x != Collision::NONE)
		{
			velocity.x = -velocity.x;
			side.x = Collision::NONE;
		}
		return side;
	}


}

void Enemy::Update(float gameTime, Keyboard* key)
{
	//Update Animation
	this->SetBound(Width, Height);
	UpdateAnimation();
	_anim->Update(gameTime);

	Object::Update(gameTime, key);
}

void Enemy::UpdateAnimation()
{
	if (State == Object::Dying)
	{
		this->SetBound(0, 0);
		this->SetVelocity(0, 0);
	}
	_anim->NewAnimationByIndex(_enemyType + this->State + _kind);
	_anim->SetPosition(D3DXVECTOR2(position.x, position.y + Height / 2));
	_anim->SetFlipFlag(FlipFlag);
}

void Enemy::SetBound(float width, float height)
{
	Width = width;
	Height = height;
	bound.left = position.x - Width / 2;
	bound.right = bound.left + Width;
	bound.top = position.y + Height;
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
	GUI::GetInstance()->Render(100 * velocity.x, { 100, 200, 150, 235 });
}