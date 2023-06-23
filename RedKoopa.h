#pragma once
#include "Enemy.h"
#include "Shell.h"

class RedKoopa : public Enemy
{
public:
	RedKoopa();
	~RedKoopa();

	void Controller();
	D3DXVECTOR2 OnCollision(Object* obj, D3DXVECTOR2 side);
	void Update(float gameTime, Keyboard* key);
};
