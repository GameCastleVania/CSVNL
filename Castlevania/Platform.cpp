#include "Platform.h"


Platform::Platform()
{}

Platform::Platform(float X, float Y, float Width, float Height)
{
	x = X;
	y = Y;
	width = Width;
	height = Height;
	platForm = NULL;
	moved = false;
	LRight = false;
	CRec = RecF(x, y, 64, 16);
}

Platform::~Platform()
{
}

void Platform::Init(LPDIRECT3DDEVICE9 D3ddv, int Range, float Speed)
{
	d3ddv = D3ddv;

	left = x - Range;
	right = x ;
	speed = Speed;
	vx = Speed;
	last_time = 0;
	platForm = new Sprite(d3ddv, "resource\\image\\other\\0.png", 64, 16, 1, 1);

}

void Platform::Update()
{
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / 60)
	{
		moved = true;
		if (x <= left) LRight = true;
		if (x >= right) LRight = false;
		if (LRight)	vx = speed;
		else vx = -speed;
		x += vx;
		last_time = now;
	}
	else
	{
		moved = false;
	}
	CRec.x = x;
	CRec.y = y + 16;
}

void Platform::Draw(int vpx, int vpy)
{
	platForm->Render(x + 32, y + 8, vpx, vpy);
}

bool Platform::IsMoved()
{
	return moved;
}