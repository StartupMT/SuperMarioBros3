#pragma once
#include "Object.h"
#include "MarioCollision.h"
#include "MarioController.h"

using namespace Define;

class Mario : public Object
{
private:
	static Mario* _mario;
public:
	enum MarioType
	{
		Small = 100,
		Big = 200,
		Raccoon = 300,
	} _marioType;

	MarioController* _marioController;
	MarioCollision* _marioCollision;
	int _state = 0;
	RECT rect_attack;
	int _live, _score = 0;

public:
	Mario();
	~Mario();

	void Init();
	void BeforeUpdate(float gameTime, Keyboard* key);
	void Update(float gameTime, Keyboard* key);
	void UpdateAnimation();
	void OnCollision(Object* obj, float gameTime);
	D3DXVECTOR2 OnCollision(Object* obj, D3DXVECTOR2 side);
	void OnCollision(Object* obj);
	void ChangeMarioType(MarioType marioType);
	void SetBound(float width, float height);
	void Render(Viewport* viewport);
	static Mario* GetInstance();
};
