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

public:
	bool isAllowJump, isAllowAttack, isAllowFly, isFall, isBake, isCount, isSpeedJump;
	float timeAttack, timeAc;
	float posStartJump;

	float maxSpeed;
	float accelerate, accDown;
	float maxJump;
	int accCount = 0;

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
	void PlayControllerF();
	void Update(float gameTime, Keyboard* key);
};