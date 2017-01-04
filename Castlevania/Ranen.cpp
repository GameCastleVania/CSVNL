#include "Ranen.h"
#define ANIMATE_RATE 5

Raven::Raven(float X, float Y)
{
	PosX = x = X;
	PosY = y = Y;
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

Raven::~Raven()
{
}

void Raven::Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon * _simon, BulletManager * _bulletManager, Explosion * _explosion)
{
	d3ddv = _d3ddv;
	simon = _simon;
	bulletManager = _bulletManager;
	if (simon->GetX() > x)
		LRight = true;
	else
		LRight = false;
	explosion = _explosion;
	RavenL = new Sprite(d3ddv, "resource\\image\\enemy\\EMap3\\Ranenleft.png", 32, 32, 5, 5);
	RavenR = new Sprite(d3ddv, "resource\\image\\enemy\\EMap3\\Ranenright.png", 32, 32, 5, 5);
}

void Raven::Update()
{
	float _x = simon->GetX() - 16;
	float _y = simon->GetY() - 32;

	if (abs(_x - x) < 200)
		ready = true;
	if (wasHit)
		HP--;
	if (ready)
	{
		visible = true;
		if (!isAttack)
		{
			if (LRight)
			{
				vx = 2;
				if (y < _y)
					vy = 2;
				else
					vy = -2;
			}
			else
			{
				vx = -2;
				if (y < _y)
					vy = 2;
				else
					vy = -2;
			}
				if (y < PosY - 50)
				{
					vx = 0;
					vy = 0;
					_TimeDelay++;
					if (_TimeDelay > 30)
					{
						isAttack = true;
					}
				}
				x += vx;
				y += vy;
			}
		else
		{
			if (MoveTo(_x, _y))
				HP = 0;
		}
		DWORD now = GetTickCount();
		if (now - last_time > 1000 / ANIMATE_RATE)
		{
			if (LRight)
			{
				if (RavenR->GetIndex() == 4)
					RavenR->SetIndex(1);
				RavenR->NextRepeat();
			}
			else
			{
				if (RavenL->GetIndex() == 4)
					RavenL->SetIndex(1);
				RavenL->NextRepeat();
			}

			last_time = now;

		}
		
	}
	if ((!exploded && HP <= 0))
	{

		explosion->Get(10, x + 18, y + 34, 7);
		exploded = true;
		visible = false;
		shooting = false;
	}
	UpdateRec();
}

void Raven::UpdateGunPoint()
{
}

void Raven::Draw(int vpx, int vpy)
{
	if (visible)
	{
		if (!exploded)
		{
			if (LRight)
				RavenR->Render(x + 16, y + 32, vpx, vpy);
			else
				RavenL->Render(x + 16, y + 32, vpx, vpy);
		}
	}
}

void Raven::BulletShoot()
{
}

bool Raven::MoveTo(float _x, float _y)
{
	float kc = sqrtf((_x - x)*(_x - x) + (_y - y)*(_y - y));
	if (kc > 3)
	{
		vx = (_x - x) / kc * 2;
		vy = (_y - y) / kc * 2;
		x += vx;
		y += vy;
	}

	if (kc < 5)
		return true;
	return false;
}
	

void Raven::UpdateRec()
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

void Raven::Destroy()
{
}
