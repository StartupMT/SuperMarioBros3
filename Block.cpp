#include "Block.h"
#include "Mario.h"

Animation* Block::GetAnimationBlock()
{
	//Tạo Animation
	Animation::DataAnimMap data;
	// Brick
	data[Block::Brick + Object::Standing] = { 28 , 31 };
	//BlockItem
	data[Block::BlockItem + Object::Standing] = { 32 , 32 };
	data[Block::BlockItem + Object::Running] = { 28 , 31 , 15 };
	data[Block::BlockItem + Object::Jumping] = { 28 , 31 };

	Animation* _animBlock = new Animation(MiscXML, MiscPNG);
	_animBlock->SetDataAnimation(data);
	return _animBlock;
}


Block::Block()
{
}

Block::~Block()
{
	delete _anim;
}

void Block::Init(D3DXVECTOR2 pos, int type, int kind)
{
	AllowDraw = false;
	Tag = Object::Block;
	_anim = GetAnimationBlock();
	velocity = D3DXVECTOR2(0, 0);
	SetState(Object::Standing);
	HP = 999;

	position = pos;
	this->_blocktype = (Block::BlockType)type;
	_kind = kind;
}

void Block::Controller()
{
}

D3DXVECTOR2 Block::OnCollision(Object* obj, D3DXVECTOR2 side)
{
	return side;
}

void Block::BeforeUpdate(float gameTime, Keyboard* key)
{
	this->Controller();
	if (State == Object::Jumping) JumpState();
}

void Block::Update(float gameTime, Keyboard* key)
{
	UpdateAnimation(gameTime);
	Object::Update(gameTime, key);
}

void Block::UpdateAnimation(float gameTime)
{
	_anim->NewAnimationByIndex(_blocktype + this->State);
	_anim->SetPosition(D3DXVECTOR2(position.x, position.y));
	_anim->SetFlipFlag(velocity.x > 0);
	_anim->Update(gameTime);
}

void Block::SetBound(float width, float height)
{
	InfoSprite::Infoframe info = _anim->GetCurrentFrameInfo();
	Width = info.w;
	Height = info.h;
	bound.left = position.x - Width / 2;
	bound.right = bound.left + Width;
	bound.top = position.y + Height / 2;
	bound.bottom = bound.top - Height;
}

void Block::Render(Viewport* viewport)
{
	//vẽ Block
	if (AllowDraw)
	{
		_anim->Render(viewport);
	}
	DrawLine::GetInstance()->DrawRect(bound);
}