#include "RedKoopa.h"
#include "Mario.h"
#include "ObjectManager.h"

RedKoopa::RedKoopa()
{
}

RedKoopa::~RedKoopa()
{
	delete _anim;
}

void RedKoopa::Controller()
{
	velocity.y = Gravity;
	if (State == Object::Jumping) JumpState();
}

D3DXVECTOR2 RedKoopa::OnCollision(Object* obj, D3DXVECTOR2 side)
{
	side = Enemy::OnCollision(obj, side);
	switch (obj->Tag)
	{
	case Object::Block:
		if (side.y == Collision::BOTTOM)
		{
			if (position.x < obj->GetBound().left)
			{
				velocity.x = EnemySpeed;
			}
			else if (position.x > obj->GetBound().right)
			{
				velocity.x = -EnemySpeed;
			}
			return side;
		}
	default:
		return side;
	}
}

void RedKoopa::Update(float gameTime, Keyboard* key)
{
	Enemy::Update(gameTime, key);

	//Create Shell
	if (State == Object::Dying && AllowDraw)
	{
		this->SetBound(0, 0);
		this->SetVelocity(0, 0);
		AllowDraw = false;
		::Shell* shell = new ::Shell(this);
		shell->Init(position, Enemy::Shell, _kind == 0 ? 0 : 1);
		ObjectManager::GetInstance()->AddObjectMap(shell);
	}
}