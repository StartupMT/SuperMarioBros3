#pragma once
#include "Object.h"

class Enemy : public Object
{
public:
	enum Enemytype
	{
		Goomba = 100, //Con nấm
		Koopa = 200, //Con rùa
		Shell = 300,
		Plant = 400,	//Cây trong tube
		FireBalls = 500,
	} _enemyType;
	float timeDead;
public:
	Enemy();
	~Enemy();

	void Init(D3DXVECTOR2 pos, int _type = Enemytype::Goomba, int kind = 0);
	void BeforeUpdate(float gameTime, Keyboard* key);
	void Update(float gameTime, Keyboard* key);
	void UpdateAnimation(float gameTime);
	void Controller();
	D3DXVECTOR2 OnCollision(Object* obj, D3DXVECTOR2 side);
	void OnCollision(Object* obj);
	void SetBound(float width = -1, float height = -1);
	void Render(Viewport* viewport);
	static Animation* GetAnimationEnemy();
};

