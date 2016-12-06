#include "FireBomb.h"


FireBomb::FireBomb()
{}


FireBomb::~FireBomb()
{}

FireBomb::FireBomb(LPDIRECT3DDEVICE9 d3ddv, Explosion* _explosion)
{
	explosion = _explosion;
	life = 0;
	fbombL = new Sprite(d3ddv, "resource\\image\\weapon\2L.png", 32, 18, 1, 1);
	fbombR = new Sprite(d3ddv, "resource\\image\\weapon\2R.png", 32, 18, 1, 1);

	CRec = RecF(0, 0, 32, 28);
}

void FireBomb::Draw(float vpx, float vpy)
{
	if (visible)
	{
		fbombL->Render(x + 16, y + 14, vpx, vpy);
		fbombR->Render(x + 16, y + 14, vpx, vpy);
	}
}

void FireBomb::Update()
{
	if (visible)
	{
		x += vx;
		y += vy;
		CRec = RecF(x, y, 32, 28);
	}

	if (life == 45) Destroy();
	life++;
}
void FireBomb::Destroy()
{
	explosion->Get(1, x, y, 5);
	visible = false;
	x = y = vx = vy = 100;
	CRec = RecF(0, 0, 0, 0);
}
