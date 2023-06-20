#pragma once
#include "Block.h"

class BlockItem : public Block
{
public:
	BlockItem();
	~BlockItem();

	void Init(D3DXVECTOR2 pos, int type = BlockType::Wall, int kind = 0);
	void Controller();
	D3DXVECTOR2 OnCollision(Object* obj, D3DXVECTOR2 side);
	void CreateItem();
};