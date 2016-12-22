#include "Candle.h"

#define ANIMATE_RATE 5


Candle::Candle()
{}

Candle::Candle(float X, float Y)
{
	x = X;
	y = Y;
	exploded = false;
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
	if (visible){
		DWORD now = GetTickCount();
		if (now - last_time > 1000 / ANIMATE_RATE)
		{
			candle->Next();
			last_time = now;

		}
	}
	if (!exploded && HP <= 0)
	{
		explosion->Get(1, x + 8, y + 16, 7);
		exploded = true;
		visible = false;
	}
}

void Candle::Draw(int vpx, int vpy)
{
	if (visible)
		if (!exploded)
			candle->Render(x + 8, y + 16, vpx, vpy);
}

void Candle::UpdateGunPoint()
{

}

void Candle::Destroy()
{
	HP = 0;

}

