#include "SuperLeaf.h"
#include "Mario.h"

SuperLeaf::SuperLeaf()
{
}

SuperLeaf::~SuperLeaf()
{
	delete _anim;
}

void SuperLeaf::Controller()
{
	velocity.y = Gravity;
	if (position.x > positionStart.x + 16)
	{
		velocity.x = -ItemSpeed * 1.5;
		velocity.y = 0.1;
	}
	else if (position.x < positionStart.x - 16)
	{
		velocity.x = ItemSpeed * 1.5;
		velocity.y = 0.1;
	}
}

void SuperLeaf::BeforeUpdate(float gameTime, Keyboard* key)
{
	this->SetBound(Width, Height);
	Controller();
	JumpState();
}

D3DXVECTOR2 SuperLeaf::OnCollision(Object* obj, D3DXVECTOR2 side)
{
	switch (obj->Tag)
	{
	case Object::Player:
		Mario::GetInstance()->_marioCollision->CheckCollisionItem(this);
		return D3DXVECTOR2(Collision::NONE, Collision::NONE);
	default:
		return D3DXVECTOR2(Collision::NONE, Collision::NONE);
	}
}