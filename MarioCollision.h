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
public:
	MarioCollision();
	~MarioCollision();

	void PlayCollisionF();

	void StandCollision();
	void RunCollision();
	void JumpCollision();


};

