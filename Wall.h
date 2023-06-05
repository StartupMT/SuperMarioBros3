#include "Object.h"
#include "GameDefine.h"
#include "Collision.h"

using namespace Define;

class Wall : public Object
{
public:
	enum Type
	{
		normal,
		ghost,
		block,
		brick,
	} _type = Type::normal;

	Wall();
	~Wall();

	void Init(D3DXVECTOR2 pos, int type = Type::normal, int kind = 0);
	void Update(float gameTime, Keyboard* key);
	void Render(Viewport* viewport);
};
