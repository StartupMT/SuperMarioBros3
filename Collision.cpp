#include "Collision.h"




Collision::Collision()
{
}

Collision::~Collision()
{
}


RECT Collision::GetBoard(RECT object, D3DXVECTOR2 distance)
{
	RECT board = object;

	if (distance.x < 0)
		board.left = object.left + distance.x;
	else if (distance.x > 0)
		board.right = object.right + distance.x;

	if (distance.y < 0)
		board.bottom = object.bottom + distance.y;
	else if (distance.y > 0)
		board.top = object.top + distance.y;

	return board;
}

//Kiểm tra có chạm 1 điểm và RECT
bool Collision::isCollision(float x, float y, RECT other)
{
	return !(x < other.left || x > other.right || y > other.top || y < other.bottom);
}

//Kiểm tra có chạm không
bool Collision::isCollision(RECT object, RECT other)
{		
	return !(object.right < other.left || object.left > other.right || object.top < other.bottom || object.bottom > other.top);
}

//Kiểm tra có lồng nhau không
bool Collision::isCollision1(RECT object, RECT other)
{
	return !(object.right <= other.left || object.left >= other.right || object.top <= other.bottom || object.bottom >= other.top);
}