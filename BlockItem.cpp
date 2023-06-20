#include "BlockItem.h"
#include "Mario.h"
#include "ObjectManager.h"

BlockItem::BlockItem()
{
}

BlockItem::~BlockItem()
{
	delete _anim;
}

void BlockItem::Init(D3DXVECTOR2 pos, int type, int kind)
{
	Block::Init(pos, type, kind);
	AllowDraw = true;
	SetState(Object::Running);
}

void BlockItem::Controller()
{
	if (State == Object::Jumping) JumpState();
	if (position.y < positionStart.y)
	{
		CreateItem();
	}
}

D3DXVECTOR2 BlockItem::OnCollision(Object* obj, D3DXVECTOR2 side)
{
	side = D3DXVECTOR2(Collision::NONE, side.y);
	switch (obj->Tag)
	{
	case Object::Item:
		if (side.y == Collision::TOP && State == Object::Jumping)
		{
			::Item* item = dynamic_cast<::Item*>(obj);
			item->StartJump(0.0f);
		}
		return side;

	default:
		return side;
	}
}

void BlockItem::CreateItem()
{
	State = Object::Standing;
	position.y = positionStart.y;
	SetVelocity(0, 0);
	Object* obj;
	switch (_kind)
	{
	case 1:
		if (Mario::GetInstance()->_marioType == Mario::Small)
		{
			obj = new ::Item();
			obj->Init(positionStart, Item::SuperMushroom, 0);
		}
		else
		{
			obj = new SuperLeaf();
			obj->Init(positionStart, Item::SuperMushroom, 1);
		}
		break;
	
	case 2:
		obj = new ::Item();
		obj->Init(positionStart, Item::UpMushroom);
		break;

	default:
		obj = new ::Item();
		obj->Init(positionStart);
		break;
	}

	obj->StartJump(0.0f);
	obj->positionStart = Mario::GetInstance()->GetPosition();
	ObjectManager::GetInstance()->AddObjectMap(obj);
}