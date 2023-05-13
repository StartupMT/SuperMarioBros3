#include "Mario.h"

Mario* Mario::_mario;

Mario::Mario()
{
	AllowDraw = true;
	Tag = Object::Player;
	pathPNG = MarioPNG;
	//Tạo Animation
	info_mario = new InfoSprite(MarioXML);
	_marioAnim = new MarioAnimation(info_mario);

	position = D3DXVECTOR2(0, 0);
	velocity = D3DXVECTOR2(0, 0);
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
}

void Mario::Init(Sprite* sprite_mario)
{
	sprite = sprite_mario;
	sprite->SetTexture(pathPNG);

	SetState(Object::Standing);
	HP = 1;
}

void Mario::Update(float gameTime, Keyboard* key)
{
	if (key->IsKeyDown(Dik_RIGHT))
	{
		SetVelocityX(RunSpeed);
		FlipFlag = true;
	}
	else if (key->IsKeyDown(Dik_LEFT))
	{
		SetVelocityX(-RunSpeed);
		FlipFlag = false;
	}
	else SetVelocityX(0.0f);
	//Chỉnh lại vị trí sau khi xét va chạm
	Object::Update(gameTime, key);
	//Update Animation
	_marioAnim->SetPosition(D3DXVECTOR2( position.x , position.y - Height / 2));
	_marioAnim->SetFlipFlag(FlipFlag);
	_marioAnim->Update(gameTime, key);
}

void Mario::Render(Viewport* viewport)
{
	//Vẽ Mario
	if (AllowDraw)
	{
		sprite->SetData(
			_marioAnim->GetRect(),
			_marioAnim->GetCenter(),
			_marioAnim->GetPosition(),
			_marioAnim->GetScale(),
			_marioAnim->GetTransform(),
			_marioAnim->GetAngle()
		);
		sprite->Render(viewport);
	}
}
