#include "Candle.h"

#define ANIMATE_RATE 5
extern int Heart;
extern int Score;

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
	text = new Font(d3ddv, 22, 514, 480);
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
		explosion->Get(10, x + 8, y + 16, 7);
		exploded = true;
		visible = false;

		srand(time(NULL));
		int a = rand() % 34 + 1;
		switch (a){
		case 14: case 24: case 34:
			explosion->Get(14, x + 8, y + 16, 7);
			break;
		case 15:
			explosion->Get(15, x + 8, y + 16, 7);
			break;
		case 16:
			explosion->Get(16, x + 8, y + 16, 7);
			break;
		case 17:
			explosion->Get(17, x + 8, y + 16, 7);
			break;
		case 18:
			explosion->Get(18, x + 8, y + 16, 7);
			break;
		case 19: case 29: case 33:
			explosion->Get(19, x + 8, y + 16, 7);
			break;
		case 20:
			explosion->Get(20, x + 8, y + 16, 7);
			break;
		default:
			explosion->Get(13, x + 8, y + 16, 7);
			break;
		}
	}
	UpdateRect();
}

void Candle::Draw(int vpx, int vpy)
{
	if (visible)
		if (!exploded)
			candle->Render(x + 8, y + 16, vpx, vpy);
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

void Candle::UpdateGunPoint()
{

}

void Candle::Destroy()
{
	HP = 0;

}

