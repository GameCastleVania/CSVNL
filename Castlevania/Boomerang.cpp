#include "Boomerang.h"
#define ANIMATE_RATE 8

Boomerang::Boomerang()
{}


Boomerang::~Boomerang()
{}

Boomerang::Boomerang(LPDIRECT3DDEVICE9 d3ddv, Explosion* _explosion, CSimon* _simon)
{
	explosion = _explosion;
	last_time = 0;
	simon = _simon;
	boomerangL = new Sprite(d3ddv, "resource\\image\\weapon\\4R.png", 28, 28, 3, 3);
	boomerangR = new Sprite(d3ddv, "resource\\image\\weapon\\4R.png", 28, 28, 3, 3);

	CRec = RecF(0, 0, 28, 28);
}

void Boomerang::Draw(float vpx, float vpy)
{
	if (fight)
	{
		if (simon->GetLRight()) boomerangR->Render(x + 10 , y , vpx, vpy);
		else if (!simon->GetLRight()) boomerangL->Render(x - 10, y , vpx, vpy);
	}
}

void Boomerang::Update()
{
	if ((x > simon->GetX() + 200) || (x < simon->GetX() - 200)) falling = true;

	if (falling)
	{
		x -= vx;
		y += vy;
	}
	else
	{
		x += vx;
		y += vy;
	}


	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{

		if (simon->GetLRight())
		{
			boomerangR->Next();

		}

		else if (!simon->GetLRight())
		{
			boomerangL->Next();
		}
		last_time = now;
	}
	CRec.x = x;
	CRec.y = y;
	CRec.vx = vx;
	CRec.vy = vy;

}
void Boomerang::Destroy()
{
	//explosion->Get(1, x, y, 5);
	fight = false;
	falling = false;
	x = y =  -100;
	vx = vy = 0;
	CRec = RecF(0, 0, 0, 0);
}
