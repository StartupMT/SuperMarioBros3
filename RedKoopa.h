#pragma once
#include "Enemy.h"

class RedKoopa : public Enemy
{
public:
	RedKoopa();
	~RedKoopa();

	void Controller();
	D3DXVECTOR2 OnCollision(Object* obj, D3DXVECTOR2 side);
};
