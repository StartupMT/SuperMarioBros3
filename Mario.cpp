#include "Mario.h"
#include <math.h>

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
	//Small
	data[Mario::Small + Object::Standing] = { 19, 19 };
	data[Mario::Small + Object::Running] = { 2,	3 };
	data[Mario::Small + Object::Running + 1] = { 2, 3, 5 };	//Chạy nhanh
	data[Mario::Small + Object::Running + 2] = { 6, 7, 1 };	//Trượt
	data[Mario::Small + Object::Running + 3] = { 4, 4 };	//Thắng
	data[Mario::Small + Object::Jumping] = { 5, 5 };
	data[Mario::Small + Object::Jumping + 1] = { 8, 8 };	//Anim chạy nhanh
	//Big
	data[Mario::Big + Object::Standing] = { 47, 47 };
	data[Mario::Big + Object::Running] = { 2,	3 };
	data[Mario::Big + Object::Running + 1] = { 2, 3, 5 };	//Chạy nhanh
	data[Mario::Big + Object::Running + 2] = { 6, 7, 1 };	//Trượt
	data[Mario::Big + Object::Running + 3] = { 4, 4 };	//Thắng
	data[Mario::Big + Object::Jumping] = { 5, 5 };
	data[Mario::Big + Object::Jumping + 1] = { 8, 8 };	//Anim chạy nhanh
	//Raccoon
	data[Mario::Raccoon + Object::Standing] = { 130, 130 };
	data[Mario::Raccoon + Object::Running] = { 2,	3 };
	data[Mario::Raccoon + Object::Running + 1] = { 2, 3, 5 };	//Chạy nhanh
	data[Mario::Raccoon + Object::Running + 2] = { 6, 7, 1 };	//Trượt
	data[Mario::Raccoon + Object::Running + 3] = { 4, 4 };	//Thắng
	data[Mario::Raccoon + Object::Jumping] = { 5, 5 };
	data[Mario::Raccoon + Object::Jumping + 1] = { 8, 8 };	//Anim chạy nhanh

	//data[Mario::Small + Object::Standing] = { 19,19 };

	_anim = new Animation(MarioXML, MarioPNG);
	_anim->SetDataAnimation(data);

	//Tạo class xử lý va chạm
	_marioController = new MarioController();
	_marioCollision = new MarioCollision();

	AllowDraw = true;
	Tag = Object::Player;
	_marioType = Mario::Small;
	this->SetBound(15, 15);
	position = D3DXVECTOR2(0, 0);
	velocity = D3DXVECTOR2(0, 0);
	SetState(Object::Standing);
	HP = 1;
}

void Mario::BeforeUpdate(float gameTime, Keyboard* key)
{
	//Update Animation
	UpdateAnimation();
	_anim->Update(gameTime);

	//Check handler controller
	_marioController->Update(gameTime, key);

	//Check mario collision by state
	_marioCollision->PlayCollisionF();
}

void Mario::Update(float gameTime, Keyboard* key)
{
	position += velocity * gameTime * 100;
	//Object::Update(gameTime, key);
}

void Mario::UpdateAnimation()
{
	int _state = 0;
	if (State == Object::Running)
	{
		_state = _marioController->isBake ? 3 : abs(velocity.x) >= MaxSpeed ? 2 : abs(velocity.x) >= MaxRun ? 1 : 0;
	}
	else if (State == Object::Jumping)
		_state = _marioController->isSpeedJump;

	_anim->NewAnimationByIndex(_marioType + this->State + _state);

	this->SetBound(Width, Height);
	_anim->SetPosition(D3DXVECTOR2(position.x, position.y + Height / 2));
	_anim->SetFlipFlag(FlipFlag);
}

void Mario::SetTexture(char* path)
{
	pathPNG = path;
	_anim->SetTexture(pathPNG);
}

void Mario::SetBound(float width, float height)
{
	//InfoSprite::Infoframe info = _anim->GetCurrentFrameInfo();
	Width = width;
	Height = height;
	bound.left = position.x - Width / 2;
	bound.right = bound.left + Width;
	bound.top = position.y + Height;
	bound.bottom = position.y;
}

void Mario::Render(Viewport* viewport)
{
	//Vẽ Mario
	if (AllowDraw)
	{
		_anim->Render(viewport);
	}
	DrawLine::GetInstance()->DrawRect(bound);
}