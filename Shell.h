#pragma once
#include "Enemy.h"

class RedKoopa;
class Shell :public Enemy
{
public:
	float _timeSpawn = 0;
	RedKoopa* _koopa;

public:
	Shell(RedKoopa* koopa);
	~Shell();

	void Init(D3DXVECTOR2 pos, int _type = Enemytype::Goomba, int kind = 0);
	void Controller();
	D3DXVECTOR2 OnCollision(Object* obj, D3DXVECTOR2 side);
	void Update(float gameTime, Keyboard* key);
};