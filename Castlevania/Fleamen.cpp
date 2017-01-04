#include "Fleamen.h"
#define ANIMATE_RATE 5

Fleamen::Fleamen(float X, float Y)
{
	PosX = x = X;
	PosY = y = Y - 14;
	LRight = true;
	exploded = false;
	shooting = false;
	type = 4;
	isDead = 0;
	HP = 1;
	vx = 0;
	vy = 0;
	CRec = RecF(x, y, 32, 32);
}

void Fleamen::Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon * _simon, BulletManager * _bulletManager, Explosion * _explosion)
{
	d3ddv = _d3ddv;
	simon = _simon;
	bulletManager = _bulletManager;
	explosion = _explosion;
	FleamenL = new Sprite(d3ddv, "resource\\image\\enemy\\EMap3\\Monkeyleft.png", 32, 32, 2, 2);
	FleamenR = new Sprite(d3ddv, "resource\\image\\enemy\\EMap3\\Monkeyright.png", 32, 32, 2, 2);
}

void Fleamen::Update()
{
	float _x = simon->GetX() - 16;
	float _y = simon->GetY() - 32;

	if (abs(_x - x) < 200 && (PosY - _y) < 200)
		ready = true;
	if (wasHit)
		HP--;
	if (ready)
	{
		visible = true;
		if(isDelay)
			_TimeDelay++;
		if (_TimeDelay > 60)
		{
			isJump = true;
			_TimeDelay = 0;
		}
		if (isJump)
		{
			if (x > _x)
				LRight = false;
			else
				LRight = true;
			if (LRight)
				vx = 2;
			else
				vx = -2;
			vy = 5;
			isJump = false;
			isDelay = false;
			isFirst = false;
		}
		else
		{
			if (!isFirst)
			{
				vy -= 0.2;
				if (PosX < 450 && PosX > 300)
				{
					if (y < PosY - 165)
					{
						vx = 0;
						vy = 0;
						isDelay = true;
					}
					if (x > 1345 || x < 250)
					{
						if (y < PosY - 135)
						{
							vx = 0;
							vy = 0;
							isDelay = true;
						}
					}
				}
				else
				{
					if (y < PosY - 95)
					{
						vx = 0;
						vy = 0;
						isDelay = true;
					}
					if (x > 1345 || x < 250)
					{
						if (y < PosY - 65)
						{
							vx = 0;
							vy = 0;
							isDelay = true;
						}
					}
				}
				if (x < 130 || x > 1500)
					vx = 0;
				
			}
		}
		DWORD now = GetTickCount();
		if (now - last_time > 1000 / ANIMATE_RATE)
		{
			if (!isDelay)
			{
				if (LRight)
					FleamenR->SetIndex(1);
				else
					FleamenL->SetIndex(1);
			}
			else
			{
				if (LRight)
					FleamenR->NextRepeat();
				else
					FleamenL->NextRepeat();
			}

			last_time = now;

		}
		x += vx;
		y += vy;
	}
	if (!exploded && HP <= 0)
	{


		explosion->Get(10, x + 18, y + 34, 7);
		exploded = true;
		visible = false;
		shooting = false;
	}
	UpdateRec();
}

void Fleamen::UpdateGunPoint()
{
}

void Fleamen::Draw(int vpx, int vpy)
{
	if (visible)
	{
		if (!exploded)
		{
			if (LRight)
				FleamenR->Render(x + 16, y + 32, vpx, vpy);
			else
				FleamenL->Render(x + 16, y + 32, vpx, vpy);
		}
	}
}

void Fleamen::BulletShoot()
{
}

void Fleamen::UpdateRec()
{
	if (HP > 0)
	{
		CRec = RecF(x, y, 32, 32);
	}
	else
	{
		CRec = RecF(0, 0, 0, 0);
	}
	if (visible == false)
		CRec = RecF(0, 0, 0, 0);
}

void Fleamen::Destroy()
{
	HP = 0;
}
