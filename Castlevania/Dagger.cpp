#include "Dagger.h"


Dagger::Dagger()
{}


Dagger::~Dagger()
{}

Dagger::Dagger(LPDIRECT3DDEVICE9 d3ddv, Explosion* _explosion)
{
	explosion = _explosion;
	life = 0;
	daggerL = new Sprite(d3ddv, "resource\\image\\weapon\1L.png", 32, 18, 1, 1);
	daggerR = new Sprite(d3ddv, "resource\\image\\weapon\1R.png", 32, 18, 1, 1);

	CRec = RecF(0, 0, 32, 28);
}

void Dagger::Draw(float vpx, float vpy)
{
	if (visible)
	{
		daggerL->Render(x + 16, y + 14, vpx, vpy);
		daggerR->Render(x + 16, y + 14, vpx, vpy);
	}
}

void Dagger::Update()
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
void Dagger::Destroy()
{
	explosion->Get(1, x, y, 5);
	visible = false;
	x = y = vx = vy = 100;
	CRec = RecF(0, 0, 0, 0);
}
