#include "Mario.h"
#include "GameDefine.h"
#include <math.h>
#include "GUI.h"

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
	Animation::DataAnimMap data;
	//Small
	data[Mario::Small + Object::Standing] = { 19, 19 };
	data[Mario::Small + Object::Running] = { 2,	3 };
	data[Mario::Small + Object::Running + 1] = { 2, 3, 5 };	//Chạy nhanh
	data[Mario::Small + Object::Running + 2] = { 6, 7, 1 };	//Trượt
	data[Mario::Small + Object::Running + 3] = { 4, 4 };	//Thắng
	data[Mario::Small + Object::Jumping] = { 5, 5 };
	data[Mario::Small + Object::Jumping + 1] = { 5, 5 };	//Rơi
	data[Mario::Small + Object::Jumping + 2] = { 8, 8 };	//Anim bay nhanh
	data[Mario::Small + Object::Dying] = { 10, 10 };	//Chết
	//Big
	data[Mario::Big + Object::Standing] = { 47, 47 };
	data[Mario::Big + Object::Running] = { 25,	27 };
	data[Mario::Big + Object::Running + 1] = { 25, 27, 5 };	//Chạy nhanh
	data[Mario::Big + Object::Running + 2] = { 31, 33, 1 };	//Trượt
	data[Mario::Big + Object::Running + 3] = { 28, 28 };	//Thắng
	data[Mario::Big + Object::Jumping] = { 29, 29 };
	data[Mario::Big + Object::Jumping + 1] = { 30, 30 };	//rơi
	data[Mario::Big + Object::Jumping + 2] = { 34, 34 };	//Anim bay nhanh
	//Raccoon
	data[Mario::Raccoon + Object::Standing] = { 130, 130 };
	data[Mario::Raccoon + Object::Running] = { 96,	98 };
	data[Mario::Raccoon + Object::Running + 1] = { 96, 98, 5 };	//Chạy nhanh
	data[Mario::Raccoon + Object::Running + 2] = { 108, 110, 1 };	//Trượt
	data[Mario::Raccoon + Object::Running + 3] = { 99, 99 };	//Thắng
	data[Mario::Raccoon + Object::Jumping] = { 106, 106 };
	data[Mario::Raccoon + Object::Jumping + 1] = { 107, 107 };		//rơi
	data[Mario::Raccoon + Object::Jumping + 2] = { 114, 114 };	//Anim bay nhanh
	data[Mario::Raccoon + Object::Jumping + 3] = { 114, 116, 5 };	//Fly
	data[Mario::Raccoon + Object::Attacking] = { 100, 105, 5 };	//Attack

	//data[Mario::Small + Object::Standing] = { 114, 116};

	//_anim = new Animation(EnemyXML, EnemyPNG);
	//_anim = new Animation(MiscXML, MiscPNG);
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
	_marioCollision->isGround = false;
	_marioCollision->isCollisionTop = false;

	this->SetBound(Width, Height);
	//Check handler controller
	_marioController->Update(gameTime, key);
}

void Mario::OnCollision(Object* obj, float gameTime)
{
	Object::OnCollision(obj, gameTime);
	if (!this->AllowDraw || obj->State == Object::Dying || this->State == Object::Dying)
		return;
	if (obj->Tag == Object::Enemy && _marioController->isAttack)
	{
		_marioCollision->AttackCollision(obj);
	}
}

D3DXVECTOR2 Mario::OnCollision(Object* obj, D3DXVECTOR2 side)
{
	_marioCollision->_obj = obj;
	_marioCollision->_side = side;
	_marioCollision->OnCollision();
	return _marioCollision->_side;
}

void Mario::OnCollision(Object* obj)
{

}

void Mario::Update(float gameTime, Keyboard* key)
{
	//Update Animation
	UpdateAnimation();
	_anim->Update(gameTime);

	Object::Update(gameTime, key);
}

void Mario::UpdateAnimation()
{
	_state = 0;
	if (State == Object::Running)
	{
		_state = _marioController->isBake ? 3 : abs(velocity.x) >= MaxSpeed ? 2 : abs(velocity.x) >= MaxRun ? 1 : 0;
		State = velocity.x == 0 ? Object::Standing : State;
	}
	else if (State == Object::Jumping)
	{
		_state = _marioController->isFly ? 3 : _marioController->isSpeedJump ? 2 : _marioController->isFallDown;
	}
	if (!_marioCollision->isGround && velocity.y < 0 && !_marioController->isFly || _marioCollision->isCollisionTop)
	{
		//if (State != Object::Dying)
		_marioController->Fall();
	}
	State = _marioController->isAttack ? Object::Attacking : State;	//check anim attack
	_anim->NewAnimationByIndex(_marioType + this->State + _state);

	if (_marioController->isAttack && _anim->GetIndex() == _anim->GetEnd()) //check end anim attack
	{
		_marioController->isAttack = false;
		_marioController->Fall();
	}

	_anim->SetPosition(D3DXVECTOR2(position.x, position.y + Height / 2));
	_anim->SetFlipFlag(FlipFlag);
}

void Mario::ChangeMarioType(MarioType marioType)
{
	//_marioType = marioType;
	//if (key->IsKeyDown(DIK_A))
	//{
	//	this->SetBound(15, 15);
	//}
	//if (key->IsKeyDown(DIK_S))
	//{
	//	mario->_marioType = Mario::Big;
	//	mario->SetBound(17, 25);
	//}
	//if (key->IsKeyDown(DIK_D))
	//{
	//	mario->_marioType = Mario::Raccoon;
	//	mario->SetBound(17, 25);
	//}
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
	GUI::GetInstance()->Render(_marioType + this->State + _state, { 100, 200, 150, 235 });
}
