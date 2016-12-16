#include "Que.h"



Que::Que()
{
}

Que::Que(float X, float Y)
{
	PosX = x = X;
	PosY = y = Y;
	LRight = true;
	exploded = false;
	shooting = false;
	isDead = 0;
	HP = 2;
	vx = 0;
	vy = 0;
	CRec = RecF(x, y, 14, 20);
}


Que::~Que()
{
}

void Que::Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon * _simon, BulletManager * _bulletManager, Explosion * _explosion)
{
	d3ddv = _d3ddv;
	simon = _simon;
	bulletManager = _bulletManager;
	explosion = _explosion;
	cay = new Sprite(d3ddv, "resource\\image\\enemy\\EMap2\\8.png", 14, 20, 1, 1);
}

void Que::Update()
{

}

void Que::UpdateGunPoint()
{
}

void Que::Draw(int vpx, int vpy)
{
	if (visible)
	{
		cay->Render(x + 16, y + 32, vpx, vpy);
	}
}

void Que::Destroy()
{
}
