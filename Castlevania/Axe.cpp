#include "Axe.h"


Axe::Axe()
{}


Axe::~Axe()
{}

Axe::Axe(LPDIRECT3DDEVICE9 d3ddv, Explosion* _explosion)
{
	explosion = _explosion;
	life = 0;
	axeL = new Sprite(d3ddv, "resource\\image\\weapon\\3L.png", 30, 28, 4, 4);
	axeR = new Sprite(d3ddv, "resource\\image\\weapon\\3R.png", 30, 28, 4, 4);

	CRec = RecF(0, 0, 30, 28);
}

void Axe::Draw(float vpx, float vpy)
{
	if (visible)
	{
		axeL->Render(x + 15, y + 14, vpx, vpy);
		axeR->Render(x + 15, y + 14, vpx, vpy);

	}
}

void Axe::Update()
{
	if (visible)
	{
		x += vx;
		y += vy;
		CRec = RecF(x, y, 30, 28);
	}

	if (life == 45) Destroy();
	life++;
}
void Axe::Destroy()
{
	explosion->Get(1, x, y, 5);
	visible = false;
	x = y = vx = vy = 100;
	CRec = RecF(0, 0, 0, 0);
}
