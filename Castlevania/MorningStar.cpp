#include "MorningStar.h"


MorningStar::MorningStar()
{}


MorningStar::~MorningStar()
{}

MorningStar::MorningStar(LPDIRECT3DDEVICE9 d3ddv, Explosion* _explosion)
{
	explosion = _explosion;
	life = 0;
	mstarL = new Sprite(d3ddv, "resource\\image\\weapon\morningstarL.png", 160, 65, 3, 3);
	mstarR = new Sprite(d3ddv, "resource\\image\\weapon\morningstarR.png", 160, 65, 3, 3);

	CRec = RecF(0, 0, 160, 65);
}

void MorningStar::Draw(float vpx, float vpy)
{
	if (visible)
	{
		mstarL->Render(x + 80, y + 32, vpx, vpy);
		mstarR->Render(x + 80, y + 32, vpx, vpy);

	}
}

void MorningStar::Update()
{
	if (visible)
	{
		x += vx;
		y += vy;
		CRec = RecF(x, y, 160, 65);
	}

	if (life == 45) Destroy();
	life++;
}
void MorningStar::Destroy()
{
	explosion->Get(1, x, y, 5);
	visible = false;
	x = y = vx = vy = 100;
	CRec = RecF(0, 0, 0, 0);
}
