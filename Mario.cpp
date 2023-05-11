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
	if (key->IsKeyDown(Dik_RIGHT))
	{
		velocity.x = RunSpeed;
		FlipFlag = true;
	}
	else if (key->IsKeyDown(Dik_LEFT))
	{
		velocity.x = -RunSpeed;
		FlipFlag = false;
	}
	else velocity.x = 0.0f;

	if (key->IsKeyDown(Dik_UP))
	{
		velocity.y = RunSpeed;
	}
	else if (key->IsKeyDown(Dik_DOWN))
	{
		velocity.y = -RunSpeed;
	}
	else velocity.y = 0.0f;

	position += velocity * gameTime * 100;

	//Update Animation
	RECT marioRect = { 0, 0, 12, 15 };
	sprite->SetRect(marioRect);
	sprite->SetPosition(position);
	sprite->Flip(FlipFlag);
	sprite->Update(gameTime, key);
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
