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
			item->StartJump();
			item->positionStart = position;
		}
		return side;
	case Object::Block:
		return D3DXVECTOR2(Collision::NONE, Collision::NONE);

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
			obj->StartJump(0.3, 9);
		}
		else
		{
			obj = new SuperLeaf();
			obj->Init(positionStart, Item::SuperMushroom, 1);
			obj->StartJump(JumpSpeed * 1.2, MaxEnemyJump * 2, Gravity / 8);
			obj->SetVelocityX(ItemSpeed);
			obj->SetPositionStart(positionStart);
			ObjectManager::GetInstance()->AddObjectMap(obj);
			return;
		}
		break;
	
	case 2:
		obj = new ::Item();
		obj->Init(positionStart, Item::UpMushroom);
		obj->StartJump(0.3, 9);
		break;

	default:
		obj = new ::Item();
		obj->Init(positionStart);
		obj->StartJump(JumpSpeed * 1.3);
		break;
	}

	obj->positionStart.x = Mario::GetInstance()->GetPosition().x;
	ObjectManager::GetInstance()->AddObjectMap(obj);
}