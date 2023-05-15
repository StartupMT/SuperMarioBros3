#include "Wall.h"

Wall::Wall()
{
	AllowDraw = true;
	Tag = Object::Wall;
	velocity = D3DXVECTOR2(0, 0);
	SetState(Object::Standing);
	oldState = Object::Dying;
	HP = 999;
}

Wall::~Wall()
{
	delete _anim;
}

void Wall::Init(Type type, D3DXVECTOR2 pos)
{

	this->_type = type;
	position = pos;
	GetBound(300, 10);
}

void Wall::Update(float gameTime, Keyboard* key)
{
	//collion

}

void Wall::Render(Viewport* viewport)
{
	if (AllowDraw)
	{
		
	}
}