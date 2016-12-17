#include "Door.h"

#define ANIMATE_RATE 7
extern int Current_State;

Door::Door()
{
}

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
	close = false;
	isopen = false;
	isclose = false;
	time = 0;
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
		switch (Current_State)
		{
		case 3:
			if (time >= 30 && time < 40) 	door1->Render(x + 55, y + 48, vpx, vpy);
			else if (time >= 40)  door2->Render(x + 55, y + 48, vpx, vpy);
			break;
		case 4:
			if (time >= 30 && time < 40) 	door1->Render(x + 55, y -15, vpx, vpy);
			else if (time >= 40)  door2->Render(x + 55, y -15, vpx, vpy);
			break;
		default:
			break;
		}
		
		if (time > 60)
		{
			isopen = true;
			isclose = false;
		}
	}
	if (close)
	{
		switch (Current_State)
		{
		case 3:
			if (time >= 90 && time < 200)  door1->Render(x + 55, y + 48, vpx, vpy);
			break;
		case 4:
			if (time >= 90 && time < 200)  door1->Render(x + 55, y - 15, vpx, vpy);
			break;
		default:
			break;
		}	
		//else if (time >= 60)  closedoor->Render(x + 22, y + 48, vpx, vpy);
		if (time > 230)
		{
			isopen = false;
			isclose = true;
		}	
	}
}

void Door::Destroy()
{
}

