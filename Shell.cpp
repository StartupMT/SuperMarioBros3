#include "Shell.h"
#include "RedKoopa.h"
#include "Mario.h"
#include "ObjectManager.h"

Shell::Shell(RedKoopa* koopa)
{
	_koopa = koopa;
}

Shell::~Shell()
{
	delete _anim;
}

void Shell::Init(D3DXVECTOR2 pos, int _type, int kind)
{
	Enemy::Init(pos, _type, kind);
	velocity = D3DXVECTOR2(0, Gravity);
	SetState(Object::Standing);
	_timeSpawn = 0;
}

void Shell::Controller()
{
	if (AllowDraw == false)
		return;

	switch (State)
	{
	case Object::Standing:
		velocity = D3DXVECTOR2(0, Gravity);
		break;
	case Object::Running:
		_timeSpawn = 0;
		if (velocity.x == 0)
			velocity.x = position.x > Mario::GetInstance()->GetPosition().x ? EnemySpeed * 3 : -EnemySpeed * 3;
		break;
	case Object::Dying:
		if (velocity.x != 0)
		{
			State = Object::Standing;
			velocity = D3DXVECTOR2(0, Gravity);
			break;
		}
		State = Object::Running;
		break;

	default:
		break;
	}
	velocity.y = Gravity;
}

D3DXVECTOR2 Shell::OnCollision(Object* obj, D3DXVECTOR2 side)
{
	switch (obj->Tag)
	{
	case Object::Player:
		if (State == Object::Running)
		{
			Mario::GetInstance()->_marioCollision->CheckCollisionEnemy();
			return D3DXVECTOR2(Collision::NONE, side.y);
		}
		State == Running;
		return side;
	case Object::Block:
		//check block
		if (dynamic_cast<::Block*>(obj))
		{
			::Block* block = dynamic_cast<::Block*>(obj);
			if (block->_blocktype == ::Block::BlockItem && block->State == Object::Running)
			{
				block->StartJump();
			}
		}
		//Đổi hướng khi đụng tường
		if (side.x != Collision::NONE)
		{
			velocity.x = -velocity.x;
			side.x = Collision::NONE;
		}
		return side;
	case Object::Enemy:
		obj->State = Object::Dying;
		return D3DXVECTOR2(Collision::NONE, Collision::NONE);

	default:
		return D3DXVECTOR2(Collision::NONE, Collision::NONE);
	}
}

void Shell :: Update(float gameTime, Keyboard* key)
{
	if (AllowDraw == false)
		return;
	if (State == Object::Dying)
	{
		this->SetBound(0, 0);
		velocity.y = 0;
	}

	//Spawn Koopa
	_timeSpawn += gameTime;
	if (_timeSpawn > 5)
	{
		_koopa->Init(position, Enemy::Koopa, _kind);
		this->SetBound(0, 0);
		this->SetVelocity(0, 0);
		AllowDraw = false;
		State = Object::Dying;
	}

	UpdateAnimation(gameTime);
	Object::Update(gameTime, key);
}