#include "Block.h"

Block::Block()
{
	AllowDraw = true;
	Tag = Object::Block;
	velocity = D3DXVECTOR2(0, 0);
	SetState(Object::Standing);
	HP = 999;
}

Block::~Block()
{
	delete _anim;
}

void Block::Init(D3DXVECTOR2 pos, int type, int kind)
{
	position = pos;
	this->_blocktype = (Block::BlockType)type;
	_kind = kind;
}

void Block::Update(float gameTime, Keyboard* key)
{
	//collion

}

void Block::Render(Viewport* viewport)
{
	if (AllowDraw)
	{
		DrawLine::GetInstance()->DrawRect(GetBound());
	}
}