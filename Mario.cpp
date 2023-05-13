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
	delete _marioController;
	delete _marioCollision;
	delete _mario;
}

void Mario::Init()
{
	//Tạo Animation
	pathPNG = MarioPNG;

	Animation::DataAnimMap data;
	data[Object::Standing] = { 19,19 };
	data[Object::Running] = { 2,	3 };
	data[Object::Jumping] = { 5,	5 };

	_anim = new Animation(MarioXML, MarioPNG);
	_anim->SetDataAnimation(data);

	//Tạo class xử lý va chạm
	_marioController = new MarioController();
	_marioCollision = new MarioCollision();

	AllowDraw = true;
	Tag = Object::Player;
	position = D3DXVECTOR2(0, 0);
	velocity = D3DXVECTOR2(0, 0);
	SetState(Object::Standing);
	oldState = Object::Dying;
	HP = 1;
}

void Mario::Update(float gameTime, Keyboard* key)
{
	//Check handler controller
	_marioController->PlayControllerF(key);

	//Check mario collision by state
	_marioCollision->PlayCollisionF();

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
		_anim->Render(viewport);
	}
}

void Mario::SetTexture(char* path)
{
	pathPNG = path;
	_anim->SetTexture(pathPNG);
}