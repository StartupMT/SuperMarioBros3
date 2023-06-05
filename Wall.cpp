#include "Wall.h"

Wall::Wall()
{
	AllowDraw = true;
	Tag = Object::Wall;
	velocity = D3DXVECTOR2(0, 0);
	SetState(Object::Standing);
	HP = 999;
}

Wall::~Wall()
{
	delete _anim;
}

void Wall::Init(D3DXVECTOR2 pos, int type, int kind)
{

	this->_type = (Wall::Type)type;
	position = pos;
}

void Wall::Update(float gameTime, Keyboard* key)
{
	//collion

}

void Wall::Render(Viewport* viewport)
{
	if (AllowDraw)
	{
		DrawLine::GetInstance()->DrawRect(GetBound());
	}
}