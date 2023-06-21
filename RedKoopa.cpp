#include "RedKoopa.h"
#include "Mario.h"

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
	side = D3DXVECTOR2(Collision::NONE, side.y);
	switch (obj->Tag)
	{
	case Object::Player:
		Mario::GetInstance()->_marioCollision->CheckCollisionEnemy();
		return side;

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
		}
		return side;
	default:
		return side;
	}
}
