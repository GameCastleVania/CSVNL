#include "Boomerang.h"


Boomerang::Boomerang()
{}


Boomerang::~Boomerang()
{}

Boomerang::Boomerang(LPDIRECT3DDEVICE9 d3ddv, Explosion* _explosion)
{
	explosion = _explosion;
	life = 0;
	boomerangL = new Sprite(d3ddv, "resource\\image\\weapon\4L.png", 28, 28, 3, 3);
	boomerangR = new Sprite(d3ddv, "resource\\image\\weapon\4R.png", 28, 28, 3, 3);

	CRec = RecF(0, 0, 28, 28);
}

void Boomerang::Draw(float vpx, float vpy)
{
	
		boomerangL->Render(x + 14, y + 14, vpx, vpy);
		boomerangR->Render(x + 14, y + 14, vpx, vpy);

	
}

void Boomerang::Update()
{
	
		x += vx;
		y += vy;
		CRec = RecF(x, y, 28, 28);
	
	if (life == 45) Destroy();
	life++;
}
void Boomerang::Destroy()
{
	explosion->Get(1, x, y, 5);
	
	x = y = vx = vy = 100;
	CRec = RecF(0, 0, 0, 0);
}
