#pragma once
#include <d3dx9.h>
#include "Keyboard.h"
#include "Object.h"
#include "GameDefine.h"
using namespace Define;

class Mario;
class MarioController
{
private:
	typedef void(MarioController::* MarioControllerF)(void);
	typedef map<int, MarioControllerF> FunctionMap;
	FunctionMap _functionMap;

protected:
	bool isAllowJump, isAllowAttack, isAllowFly, isFall;
	float timeAttack;
	float posStartJump;
	Mario* mario;
	Keyboard* key;
public:
	MarioController();
	~MarioController();

	void Fall();//Rơi
	void StandState();
	void RunState();
	void MoveX();
	void JumpState();
	void AttackState();
	void DeadState();
	void PlayControllerF(Keyboard* key);
};