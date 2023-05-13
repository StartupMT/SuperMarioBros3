#include "Mario.h"

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
	delete _marioCollision;
	delete _mario;
}

void Mario::Init()
{
	//Tạo Animation
	pathPNG = MarioPNG;

	Animation::DataAnim data[] = {
		{Object::Standing,	0,	0,	0},
		{Object::Running,	1,	2,	20},
		{Object::Jumping,	7,	7,	0},
	};
	_anim = new Animation(MarioXML, MarioPNG);
	_anim->SetDataAnimation(data);

	//Tạo class xử lý va chạm
	_marioCollision = new MarioCollision();

	AllowDraw = true;
	Tag = Object::Player;
	position = D3DXVECTOR2(0, 0);
	velocity = D3DXVECTOR2(0, 0);
	SetState(Object::Standing);
	HP = 1;
}

void Mario::Update(float gameTime, Keyboard* key)
{
	//Check handler controller
	if (key->IsKeyDown(Dik_RIGHT))
	{
		SetVelocityX(RunSpeed);
		FlipFlag = false;
		State = Running;
	}
	else if (key->IsKeyDown(Dik_LEFT))
	{
		SetVelocityX(-RunSpeed);
		FlipFlag = true;
		State = Running;
	}
	else
	{
		SetVelocityX(0.0f);
		State = Standing;
	}

	//Check mario collision by state
	//_marioCollision->PlayCollisionF();
	//Chỉnh lại vị trí sau khi xét va chạm
	Object::Update(gameTime, key);

	//Update Animation
	UpdateAnimation(gameTime);
	oldState = State;
}

void Mario::UpdateAnimation(float gameTime)
{
	if (State != oldState)
		_anim->NewAnimationByIndex(State);

	_anim->SetPosition(D3DXVECTOR2(position.x, position.y - Height / 2));
	_anim->SetFlipFlag(FlipFlag);
	_anim->Update(gameTime);
}

void Mario::Render(Viewport* viewport)
{
	//Vẽ Mario
	if (AllowDraw)
	{
		//_anim->SetData(
		//	_anim->GetRect(),
		//	_anim->GetCenter(),
		//	_anim->GetPosition(),
		//	_anim->GetScale(),
		//	_anim->GetTransform(),
		//	_anim->GetAngle()
		//);
		_anim->Render(viewport);
	}
}

void Mario::SetTexture(char* path)
{
	pathPNG = path;
	_anim->SetTexture(pathPNG);
}