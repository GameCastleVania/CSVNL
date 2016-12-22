#include "Dagger.h"
#define ANIMATE_RATE 8

Dagger::Dagger()
{}


Dagger::~Dagger()
{}

Dagger::Dagger(LPDIRECT3DDEVICE9 d3ddv, Explosion* _explosion, CSimon* _simon)
{
	explosion = _explosion;
	last_time = 0;
	simon = _simon;

	daggerL = new Sprite(d3ddv, "resource\\image\\weapon\\1L.png", 32, 18, 1, 1);
	daggerR = new Sprite(d3ddv, "resource\\image\\weapon\\1R.png", 32, 18, 1, 1);
	CRec = RecF(0, 0, 32, 18);
}

void Dagger::Draw(float vpx, float vpy)
{
	if (fight)
	{
		if (simon->GetLRight()) daggerR->Render(x + 10, y, vpx, vpy);
		else if (!simon->GetLRight()) daggerL->Render(x - 10, y, vpx, vpy);
	}
}

void Dagger::Update()
{
	x += vx;
	y += vy;
	CRec.x = x;
	CRec.y = y;
	CRec.vx = vx;
	CRec.vy = vy;

}
void Dagger::Destroy()
{
	//explosion->Get(1, x, y, 5);
	fight = false;
	x = y = vx = vy = -100;
	CRec = RecF(0, 0, 0, 0);
}
