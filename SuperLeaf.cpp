#include "SuperLeaf.h"
#include "Mario.h"

SuperLeaf::SuperLeaf()
{
	StartJump(JumpSpeed, Gravity / 3);
}

SuperLeaf::~SuperLeaf()
{
	delete _anim;
}

void SuperLeaf::Controller()
{
	velocity.y = Gravity;
}

void SuperLeaf::BeforeUpdate(float gameTime, Keyboard* key)
{
	this->SetBound(Width, Height);
	JumpState();
}

D3DXVECTOR2 SuperLeaf::OnCollision(Object* obj, D3DXVECTOR2 side)
{
	Item::OnCollision(obj, side);
	return D3DXVECTOR2(Collision::NONE, Collision::NONE);
}