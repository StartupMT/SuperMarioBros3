#include "Object.h"
#include "GameDefine.h"
#include "Collision.h"

using namespace Define;

class Block : public Object
{
public:
	enum BlockType
	{
		Wall = 100,
		Brick = 200,
		Tube = 300,
	} _blocktype = BlockType::Wall;

	Block();
	~Block();

	void Init(D3DXVECTOR2 pos, int type = BlockType::Wall, int kind = 0);
	void Update(float gameTime, Keyboard* key);
	void Render(Viewport* viewport);
};
