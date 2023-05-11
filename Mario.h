#pragma once
#include "Keyboard.h"
#include "Viewport.h"
#include "Animation.h"
#include "GameDefine.h"

using namespace Define;

class Mario
{
private:
	static Mario* _mario;
protected:
	Sprite* sprite;
	bool FlipFlag;
	D3DXVECTOR2 position; //vị trí vẽ
	D3DXVECTOR2 velocity;//Vector vận tốc
public:
	Mario(); 
	~Mario();
	const char* pathPNG;

	void Init(Sprite* sprite_mario);
	void Update(float gameTime, Keyboard* key);
	void Render(Viewport* viewport);
	static Mario* GetInstance();

	D3DXVECTOR2 GetPosition();
	void SetPosition(D3DXVECTOR2 Position);
	D3DXVECTOR2 GetVelocity();
	void SetVelocity(D3DXVECTOR2 Velocity);
};

