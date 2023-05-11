#pragma once
#include "Viewport.h"
#include "GameDefine.h"
using namespace Define;

class Map
{
protected:
	
public:
	
	Map();
	
	~Map();
	
	int GetData(D3DXVECTOR2 pos);
	void SetData(D3DXVECTOR2 position, int data);

	void Update(float gameTime);
	void Render(Viewport * view);
};

