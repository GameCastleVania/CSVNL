#include "DragonSkullCannon.h"

DragonSkullCannon::DragonSkullCannon(float X, float Y)
{
	PosX = x = X;
	PosY = y = Y;
	LRight = true;
	exploded = false;
	shooting = true;
	isShooting = false;
	shootST = true;
	isDead = 0;
	HP = 6;
	vx = 0;
	vy = 0;
	CRec = RecF(x, y, 32, 64);
}

DragonSkullCannon::~DragonSkullCannon()
{
}

void DragonSkullCannon::Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon * _simon, BulletManager * _bulletManager, Explosion * _explosion)
{
	d3ddv = _d3ddv;
	simon = _simon;
	bulletManager = _bulletManager;
	explosion = _explosion;
	DSkullL = new Sprite(d3ddv, "resource\\image\\enemy\\EMap2\\5L.png", 32, 64, 1, 1);
	DSkullR = new Sprite(d3ddv, "resource\\image\\enemy\\EMap2\\5R.png", 32, 64, 1, 1);
}

void DragonSkullCannon::Update()
{

	float _x = simon->GetX() - 16;
	float _y = simon->GetY() - 32;

	visible = true;
	if (simon->GetX() > x)
		LRight = true;
	else
		LRight = false;
	if (shooting)
	{
		count++;
		if (count > 300 && shootST)
		{
			isShooting = true;
			shootST = false;
		}
		if (count > 320)
		{
			isShooting = true;
			count = 0;
			shootST = true;
		}
		if (isShooting)
			BulletShoot();
	}

	if (!exploded && HP <= 0)
	{
		explosion->Get(1, x + 18, y + 34, 7);
		exploded = true;
		visible = false;
		shooting = false;
	}
}

void DragonSkullCannon::UpdateGunPoint()
{

}

void DragonSkullCannon::Draw(int vpx, int vpy)
{
	if (visible)
	{
		if (!exploded)
		{
			if (!LRight)
				DSkullL->Render(x + 16, y + 32, vpx, vpy);
			else
				DSkullR->Render(x + 16, y + 32, vpx, vpy);
		}
	}
}

void DragonSkullCannon::BulletShoot()
{
	if (LRight)
	{
		bulletManager->Get(BulletType::Fire_ball, this->x, this->y + 40, 5, 0, false);
	}
	else
		bulletManager->Get(BulletType::Fire_ball, this->x, this->y + 40, -5, 0, false);
	isShooting = false;

}

void DragonSkullCannon::Destroy()
{
	HP = 0;
}
