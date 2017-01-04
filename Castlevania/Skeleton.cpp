#include "Skeleton.h"

#define ANIMATE_RATE 5




Skeleton::Skeleton(float X, float Y)
{
	PosX = x = X;
	PosY = y = Y;
	LRight = true;
	exploded = false;
	shooting = true;
	type = 4;
	isDead = 0;
	HP = 1;
	vx = 1.5;
	vy = 0;
	CRec = RecF(x, y, 32, 64);
}

Skeleton::~Skeleton()
{
}

void Skeleton::Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon * _simon, BulletManager * _bulletManager, Explosion * _explosion)
{
	d3ddv = _d3ddv;
	simon = _simon;
	bulletManager = _bulletManager;
	if (simon->GetX() > x)
		LRight = true;
	else
		LRight = false;
	explosion = _explosion;
	skeleL = new Sprite(d3ddv, "resource\\image\\enemy\\EMap3\\BXleft.png", 32, 64, 2, 2);
	skeleR = new Sprite(d3ddv, "resource\\image\\enemy\\EMap3\\BXright.png", 32, 64, 2, 2);
}

void Skeleton::Update()
{
	float _x = simon->GetX() - 16;
	float _y = simon->GetY() - 32;

	if (abs(_x - x) < 200 && abs(PosY - _y) < 100)
		ready = true;
	if (wasHit)
		HP--;
	if (ready)
	{
		_TimeFire++;
		if (x > _x)
			LRight = false;
		else
			LRight = true;
		if (x > PosX + 20)
			vx = -1.5;
		if (x < PosX - 20)
			vx = 1.5;
		if (_TimeFire > 120)
		{
			isFire = true;
			_TimeFire = 0;
		}
		if (isFire && shooting)
			BulletShoot();
		DWORD now = GetTickCount();
		if (now - last_time > 1000 / ANIMATE_RATE)
		{
			if (LRight)
			{

				skeleR->NextRepeat();
			}
			else
			{
				skeleL->NextRepeat();
			}

			last_time = now;

		}
		x += vx;
	}
	if (!exploded && HP <= 0)
	{
		ready = false;
		explosion->Get(10, x + 18, y + 34, 7);
		exploded = true;
		visible = false;
		shooting = false;
	}
	UpdateRec();
}

void Skeleton::UpdateGunPoint()
{
}

void Skeleton::Draw(int vpx, int vpy)
{
	if (visible)
	{
		if (!exploded)
		{
			if (LRight)
				skeleR->Render(x + 16, y + 32, vpx, vpy);
			else
				skeleL->Render(x + 16, y + 32, vpx, vpy);
		}
	}
}

void Skeleton::BulletShoot()
{
	isFire = false;
	if(LRight)
		bulletManager->Get(Bone_Bullet, x, y + 50, 2, 5, 0);
	else
		bulletManager->Get(Bone_Bullet, x, y +50, -2, 5, 0);
}

void Skeleton::UpdateRec()
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

void Skeleton::Destroy()
{
	HP = 0;
}
