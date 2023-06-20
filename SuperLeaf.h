#pragma once
#include "Item.h"

class SuperLeaf : public Item
{
public:
	SuperLeaf();
	~SuperLeaf();

	void Controller();
	void BeforeUpdate(float gameTime, Keyboard* key);
	D3DXVECTOR2 OnCollision(Object* obj, D3DXVECTOR2 side);
};