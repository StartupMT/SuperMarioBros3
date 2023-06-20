#include "Item.h"
#include "Mario.h"

Animation* Item::GetAnimationItem()
{
	//Tạo Animation
	Animation::DataAnimMap data;
	// Coin
	data[Item::Coin + Object::Standing] = { 0 , 5 };

	// SuperMushroom
	data[Item::SuperMushroom + Object::Standing] = { 6 , 6 };
	data[Item::SuperMushroom + Object::Standing + 1] = { 8 , 8 };

	Animation* _animItem = new Animation(MiscXML, MiscPNG);
	_animItem->SetDataAnimation(data);
	return _animItem;
}

Item::Item()
{
}

Item::~Item()
{
	delete _anim;
}

void Item::Init(D3DXVECTOR2 pos, int _type, int kind)
{
	AllowDraw = true;
	Tag = Object::Item;

	_anim = GetAnimationItem();
	_itemtype = (Itemtype)_type;
	_kind = kind;
	position = pos;
	velocity = D3DXVECTOR2(0, 0);
	SetState(Object::Standing);
	this->SetBound(16, 16);
	HP = 1;
}

void Item::Controller()
{
	velocity = D3DXVECTOR2(0, 0);
}

D3DXVECTOR2 Item::OnCollision(Object* obj, D3DXVECTOR2 side)
{
	switch (obj->Tag)
	{
	case Object::Player:
		Mario::GetInstance()->_marioCollision->CheckCollisionItem(this);
		return D3DXVECTOR2(Collision::NONE, Collision::NONE);
	case Object::Block:
		if (side.x !=Collision::NONE)
		{
			velocity.x = -velocity.x;
			side.x = Collision::NONE;
		}
		return side;
	default:
		return D3DXVECTOR2(Collision::NONE, Collision::NONE);
	}
}

void Item::OnCollision(Object* obj)
{
	if (obj->Tag == Object::Player)
		Mario::GetInstance()->_marioCollision->CheckCollisionItem(this);
}

void Item::BeforeUpdate(float gameTime, Keyboard* key)
{
	this->SetBound(Width, Height);
	this->Controller();
	if (State == Object::Jumping) JumpState();
}

void Item::Update(float gameTime, Keyboard* key)
{
	//Update Animation
	if (State == Object::Dying)
	{
		this->SetBound(0, 0);
		this->SetVelocity(0, 0);
		AllowDraw = false;
	}

	UpdateAnimation(gameTime);

	Object::Update(gameTime, key);
}

void Item::UpdateAnimation(float gameTime)
{
	_anim->NewAnimationByIndex(_itemtype + this->State + _kind);
	_anim->SetPosition(D3DXVECTOR2(position.x, position.y + Height / 2));
	_anim->SetFlipFlag(velocity.x > 0);
	_anim->Update(gameTime);
}

void Item::SetBound(float width, float height)
{
	Width = width;
	Height = height;
	bound.left = position.x - Width / 2;
	bound.right = bound.left + Width;
	bound.top = position.y + Height;
	bound.bottom = position.y;
}

void Item::Render(Viewport* viewport)
{
	//Vẽ Item
	if (AllowDraw)
	{
		_anim->Render(viewport);
	}
	DrawLine::GetInstance()->DrawRect(bound);
}