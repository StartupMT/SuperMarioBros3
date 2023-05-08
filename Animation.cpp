#include "Animation.h"


Animation::Animation()
{
	delay = 0;
	start = 0;
	end = 0;
	scale = D3DXVECTOR2(1, 1);
	position = D3DXVECTOR2(0, 0);
	angle = 0;
	Pause = false;
}

Animation::~Animation()
{
}

void Animation::SetFrame(D3DXVECTOR2 Position, bool Flip, int Delay, int Start, int End)
{
	position = Position;
	delay = Delay;
	start = Start;
	end = End;
}

int Animation::GetIndex()
{
	return Index;
}

void Animation::SetIndex(int index)
{
	Index = index;
}

int Animation::GetDelay()
{
	return delay;
}

int Animation::GetStart()
{
	return start;
}

int Animation::GetEnd()
{
	return end;
}

void Animation::SetPause(bool pause)
{
	Pause = pause;
}
void Animation::SetPause(bool pause, int index)
{
	IndexPause = index;
	Pause = pause;
}

void Animation::Update(float gameTime, Keyboard* key)
{
	//Chuyển frame tiếp theo
	if (TimeCurrent*100 >= delay )
	{
		TimeCurrent = 0;
		Index++;
	}
	else TimeCurrent += gameTime;
	//Lấy center
	center.x = (rect.right - rect.left)/2;
	center.y = (rect.bottom - rect.top) / 2;
}