#include "Candle.h"

#define ANIMATE_RATE 8


Candle::Candle()
{}

Candle::Candle(float X, float Y)
{
	x = X;
	y = Y;
	exploded = false;
	type = 9;
	isDead = 0;
	HP = 1;
	CRec = RecF(x, y, 16, 32);
}

void Candle::Init(LPDIRECT3DDEVICE9 D3ddv, CSimon* Simon, BulletManager* BulletManager, Explosion* Explosion)
{
	d3ddv = D3ddv;
	simon = Simon;
	bulletManager = BulletManager;
	explosion = Explosion;
	candle = new Sprite(d3ddv, "resource\\image\\other\\1.png", 16, 32, 2, 2);

}

void Candle::Update()
{
	if (HP <= 0)
	{
		visible = false;
	}
	UpdateRect();
}

void Candle::Draw(int vpx, int vpy)
{
	if (visible)
	candle->Render(x + 8, y + 16, vpx, vpy);
}

void Candle::UpdateGunPoint()
{
	
}


void Candle::UpdateRect()
{
	if (HP > 0)
	{
		CRec = RecF(x, y, 16, 32);
	}
	else
	{
		CRec = RecF(0, 0, 0, 0);
	}
	if (visible == false)
		CRec = RecF(0, 0, 0, 0);
}
void Candle::Destroy()
{
	HP = 0;

}

