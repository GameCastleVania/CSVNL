#include "Door.h"

#define ANIMATE_RATE 8


Door::Door()
{}

Door::~Door()
{}

Door::Door(LPDIRECT3DDEVICE9 d3ddv, CSimon* _simon, float X, float Y)
{
	x = X;
	y = Y;
	simon = _simon;
	door1 = new Sprite(d3ddv, "resource\\image\\other\\door1.png", 96, 96, 1, 1);
	door2 = new Sprite(d3ddv, "resource\\image\\other\\door2.png", 96, 96, 1, 1);
	closedoor = new Sprite(d3ddv, "resource\\image\\other\\CloseGat.png", 44, 96, 1, 1);
	open = false;
	CRec = RecF(x, y, 48, 48);
}

void Door::Update()
{
	if (open || close)
	{
		time++;
	}
}

void Door::Draw(int vpx, int vpy)
{
	if (open)
	{
		if (time >= 95 && time < 100) 	door1->Render(x + 48, y + 48, vpx, vpy);
		else if (time >= 100)  door2->Render(x + 48, y + 48, vpx, vpy);
	}
	if (close)
	{
		if (time >= 170 && time < 175)  door1->Render(x + 48, y + 48, vpx, vpy);
		else if (time >= 175)  closedoor->Render(x + 22, y + 48, vpx, vpy);
	}
}

void Door::Destroy()
{
}

