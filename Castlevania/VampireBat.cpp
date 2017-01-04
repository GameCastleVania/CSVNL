#include "VampireBat.h"

#define ANIMATE_RATE 5
VampireBat::VampireBat(float X, float Y)
{
	PosX = x = X;
	PosY = y = Y;
	LRight = true;
	exploded = false;
	shooting = false;
	isDead = 0;
	HP = 1;
	type = 4;
	vx = 1.2;
	vy = 0;
	CRec = RecF(x, y, 32, 64);
}

VampireBat::~VampireBat()
{
}

void VampireBat::Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon * _simon, BulletManager * _bulletManager, Explosion * _explosion)
{
	d3ddv = _d3ddv;
	simon = _simon;
	bulletManager = _bulletManager;
	explosion = _explosion;
	BatLR = new Sprite(d3ddv, "resource\\image\\enemy\\EMap2\\0.png", 30, 32, 4, 4);

}

void VampireBat::Update()
{
	float _x = simon->GetX() - 16;
	float _y = simon->GetY() - 32;
	
	if (abs(_x - x) < 200 &&  (PosY - _y) < 100)
		ready = true;
	if (ready)
	{
		visible = true;
		vx = 2.5;
		x += vx;
		vy = -2.5;
		if (y < PosY - 80)
			vy = 0;
		y += vy;
		DWORD now = GetTickCount();
		if (now - last_time > 1000 / ANIMATE_RATE)
		{
			if (BatLR->GetIndex() == 3)
				BatLR->SetIndex(1);
			BatLR->NextRepeat();
			last_time = now;
		}
	}
	if ((!exploded && HP <= 0))
	{
		explosion->Get(10, x + 15, y + 16, true);
		exploded = true;
		visible = false;
		shooting = false;
	}
	UpdateRec();
}

void VampireBat::UpdateGunPoint()
{
}

void VampireBat::Draw(int vpx, int vpy)
{
	if (visible)
	{
		if (!exploded)
		{
			BatLR->Render(x + 16, y + 32, vpx, vpy);
		}
	}
}

void VampireBat::BulletShoot()
{
}

void VampireBat::UpdateRec()
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

void VampireBat::Destroy()
{
	HP = 0;
}
