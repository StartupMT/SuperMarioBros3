#pragma once
#include "Collision.h"
#include "Object.h"
#include "GameDefine.h"

using namespace Define;
class Mario;
class MarioCollision : public Collision
{
private:
	typedef void(MarioCollision::* marioCollisionF)(void);
	typedef map<int, marioCollisionF> FunctionMap;
	FunctionMap _functionMap;
protected:
	Mario* mario;
	bool isSpeed, isJump, isBake;
public:
	MarioCollision();
	~MarioCollision();

	void OnCollision();
	void PlayCollisionF();

	void StandCollision();
	void RunCollision();
	void JumpCollision();
	void AttackCollision();

};

