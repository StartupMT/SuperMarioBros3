#include "Mario.h"

Mario* Mario::_mario;

Mario::Mario()
{
	pathPNG = MarioPNG;
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
	delete sprite;
}

void Mario::Init(Sprite* sprite_mario)
{
	sprite = sprite_mario;
}

void Mario::Update(float gameTime, Keyboard* key)
{
	
}

D3DXVECTOR2 Mario::GetPosition()
{
	return position;
}
void Mario::SetPosition(D3DXVECTOR2 Position)
{
	position = Position;
}

D3DXVECTOR2 Mario::GetVelocity()
{
	return velocity;
}
void Mario::SetVelocity(D3DXVECTOR2 Velocity)
{
	velocity = Velocity;
}

void Mario::Render(Viewport* viewport)
{
	sprite->Render(viewport);
}
