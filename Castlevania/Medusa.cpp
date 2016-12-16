#include "Medusa.h"
#include <iostream>

#define ANIMATE_RATE 5
#define DG_TO_RAD(x) (x * 3.141592654 / 180)

Medusa::Medusa(float X, float Y)
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
	CRec = RecF(x, y, 28, 28);
}

Medusa::~Medusa()
{
}

void Medusa::Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon * _simon, BulletManager * _bulletManager, Explosion * _explosion)
{
	d3ddv = _d3ddv;
	simon = _simon;
	bulletManager = _bulletManager;
	explosion = _explosion;
	if (simon->GetX() > x)
		LRight = true;
	else
		LRight = false;
	MedusaL = new Sprite(d3ddv, "resource\\image\\enemy\\EMap2\\4L.png", 32, 32, 2, 2);
	MedusaR = new Sprite(d3ddv, "resource\\image\\enemy\\EMap2\\4R.png", 32, 32, 2, 2);
}

void Medusa::Update()
{

	float _x = simon->GetX() - 16;
	float _y = simon->GetY() - 32;

	if (abs(_x - x) < 300 && (PosY - _y) < 100)
		ready = true;
	if (ready)
	{
		visible = true;
		if (LRight)
			vx = 2.5;
		else
			vx = -2.5;
		/*if (y <= PosY - 100)
		vy = 2;
		if (y >= PosY)
		vy = -2;*/
		x += vx;
		y -= sin(DG_TO_RAD(vy)) * 3;
		vy += 3;
		DWORD now = GetTickCount();
		if (now - last_time > 1000 / ANIMATE_RATE)
		{
			if (LRight)
				MedusaR->NextRepeat();
			else
				MedusaL->NextRepeat();
			last_time = now;

		}
	}
	
	if ((!exploded && HP <= 0) || abs(x - _x) > 900)
	{
		if (!abs(x - _x) > 900)
		{
			explosion->Get(1, x + 18, y + 34, 7);
			exploded = true;
		}
		
		visible = false;
		shooting = false;
	}
}

void Medusa::UpdateGunPoint()
{
}

void Medusa::Draw(int vpx, int vpy)
{
	if (visible)
	{
		if (!exploded)
		{
			if (!LRight)
				MedusaL->Render(x + 16, y + 32, vpx, vpy);
			else
				MedusaR->Render(x + 16, y + 32, vpx, vpy);
		}
	}
}

void Medusa::BulletShoot()
{
}

void Medusa::UpdateRec()
{
	if (HP > 0)
	{
		CRec = RecF(x, y, 32, 64);
	}
	else
	{
		CRec = RecF(0, 0, 0, 0);
	}
	if (visible == false)
		CRec = RecF(0, 0, 0, 0);
}

void Medusa::Destroy()
{
}
