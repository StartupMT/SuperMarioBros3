#include "Viewport.h"



Viewport::Viewport()
{
}

Viewport::Viewport(float x, float y)
{
	this->positionWorld.x =x;
	this->positionWorld.y =y;
	//Mặc định là kích thước game
	this->Width = GameWidth;
	this->Height = GameHeight;
}

Viewport::Viewport(float x, float y, float width, float height)
{
	this->positionWorld.x = x;
	this->positionWorld.y = y;
	this->Width = width;
	this->Height = height;
}

Viewport::~Viewport()
{
}

//Get set vị trí Viewport
D3DXVECTOR2 Viewport::GetPosition()
{
	return positionWorld;
}
void Viewport::SetPosition(D3DXVECTOR2 Position)
{
	positionWorld = Position;
}
void Viewport::SetPositionX(float x)
{
	positionWorld.x = x;	
}
void Viewport::SetPositionY(float y)
{
	positionWorld.y = y;
}

//Lấy chiều dài rộng của Viewport
float Viewport::GetWidth()
{
	return this->Width;
}
float Viewport::GetHeight()
{
	return this->Height;
}

//Lấy vị trí của ViewPort từ vị trị object cần vẽ theo hệ trục left-top
D3DXVECTOR2 Viewport::GetPositionViewport_Left_Top(D3DXVECTOR2 Position)
{
	return Position-positionWorld;
}

//Lấy vị trí của ViewPort từ vị trị object cần vẽ theo hệ đề các
D3DXVECTOR2 Viewport::GetPositionViewport(D3DXVECTOR2 Position)
{
	//int để vị trí ViewPort không lệch pixel
	float x = positionWorld.x - (int)positionWorld.x;
	float y = positionWorld.y - (int)positionWorld.y;
	D3DXVECTOR3* position = &D3DXVECTOR3(Position.x + x, Position.y + y, 0);

	D3DXMATRIX mt;
	D3DXVECTOR4 posViewport;

	//đổi ma trận chuẩn bị nhân lấy tọa độ mới
	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = -positionWorld.x;
	mt._42 = positionWorld.y;

	D3DXVec3Transform(&posViewport, position, &mt);

	return D3DXVECTOR2(posViewport.x, posViewport.y);
}

//Kiểm tra 1 rect có ở trong màn hình không
bool Viewport::isContains(RECT rect)
{
	if (rect.right < positionWorld.x)
		return false;
	if (rect.bottom > positionWorld.y)
		return false;
	if (rect.left > positionWorld.x + Width)
		return false;
	if (rect.top < positionWorld.y - Height)
		return false;

	return true;
}

//Kích thước RECT màn hình tính trong World
RECT Viewport::GetBoundViewport()
{
	RECT rect;

	rect.left = positionWorld.x;
	rect.top = positionWorld.y;
	rect.bottom = rect.top - Height;
	rect.right = rect.left + Width;

	return rect;
}

//Update theo 1 đối tượng
void Viewport::Update(float gameTime, Keyboard* key, D3DXVECTOR2 &posobject, std::vector <RECT> SceneZoom)
{
}