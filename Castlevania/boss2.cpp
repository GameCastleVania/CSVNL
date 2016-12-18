#include "Boss2.h"

#define ANIMATE_RATE 5
#define DG_TO_RAD(x) (x * 3.141592654 / 180)
Boss2::Boss2(float X, float Y)
{
	PosX = x = X;
	PosY = y = Y;
	LRight = true;
	exploded = false;
	shooting = true;
	wasHit = false;
	hitTime = 0;
	isDead = 0;
	HP = 16;
	vx = 2;
	vy = 0;
	CRec = RecF(x, y, 64, 64);
}

Boss2::~Boss2()
{
}

void Boss2::Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon * _simon, BulletManager * _bulletManager, Explosion * _explosion)
{
	d3ddv = _d3ddv;
	simon = _simon;
	bulletManager = _bulletManager;
	explosion = _explosion;
	_Boss2Idle = new Sprite(d3ddv, "resource\\image\\boss\\BMap2\\0.png", 64, 64, 1, 1);
	_Boss2Move = new Sprite(d3ddv, "resource\\image\\boss\\BMap2\\1.png", 64, 64, 4, 4);
}
void Boss2::Update()
{

	float _x = simon->GetX() - 32;
	float _y = simon->GetY() - 32;
	float kc = sqrtf((_x - PosX)*(_x - PosX) + (_y - PosY)*(_y - PosY));
	float kc2 = sqrtf((_x - x)*(_x - x) + (_y - y)*(_y - y));
	if (wasHit)
		HP--;
	if (HP <= 10)
		ready = true;
	if (ready)
	{
		if (!wasHit)
		{
			
			if (kc < 100)
			{
				MoveTo(_x, _y);
				IsFinish = false;
			}
			else
			{
				if (!IsFinish)
					MoveTo(PosX, PosY);
				else
				{
					if (shooting)
					{
						count++;

						if (count > 100)
						{
							isShooting = true;
							count = 0;

						}
						if (isShooting)
							BulletShoot((_x - x) / kc2 * 3, (_y - y) / kc2 * 3);
					}
					vy++;
					if (vy > 360)
					{

						vy = 0;
					}
					else
					{

						if (LRight)
						{
							if (vy >= 0 && vy < 90 || vy >= 270)
								vx = 2;
							if (vy >= 90 && vy < 270)
								vx = -2;
						}
						else
						{
							if (vy >= 0 && vy < 90 || vy >= 270)
								vx = -2;
							if (vy >= 90 && vy < 270)
								vx = 2;
						}
					}
					y += sin(DG_TO_RAD(vy));
					x += vx;
				}
				
			}
			DWORD now = GetTickCount();
			if (now - last_time > 1000 / ANIMATE_RATE)
			{
				_Boss2Move->NextRepeat();
				last_time = now;
			}	

		}
		else
		{
			if (vx != 0)
				vxbackup = vx;
			if (vy != 0)
				vybackup = vy;
			vx = 0;
			vy = 0;
			hitTime++;
			if (hitTime > 30)
			{
				hitTime = 0;
				vx = vxbackup;
				vy = vybackup;
				wasHit = false;
			}
		}
	}
	if (!exploded && HP <= 0)
	{
		explosion->Get(1, x + 18, y + 34, 7);
		exploded = true;
		visible = false;
		shooting = false;
	}
	UpdateRec();
}

void Boss2::UpdateGunPoint()
{
}

void Boss2::Draw(int vpx, int vpy)
{
	if (visible)
	{
		if (!exploded)
		{
			if (ready)
				_Boss2Move->Render(x + 32, y + 32, vpx, vpy);
			else
				_Boss2Idle->Render(x + 32, y + 32, vpx, vpy);
		}
	}
}

void Boss2::BulletShoot(float _vx, float _vy)
{
	bulletManager->Get(2, this->x, this->y, _vx, _vy);
	isShooting = false;
}

bool Boss2::MoveTo(float _x, float _y)
{
	float kc = sqrtf((_x - x)*(_x - x) + (_y - y)*(_y - y));
	if (kc != 0)
	{
		vx = (_x - x) / kc * 2;
		vy = (_y - y) / kc * 2;
	}
	x += vx;
	y += vy;
	if (kc <= 5)
	{		
		IsFinish = true;
		vy = 0;
		return true;
	}
	else
	{
		return false;		
	}
}

void Boss2::UpdateRec()
{
	if (HP > 0)
	{
		CRec = RecF(x, y, 64, 64);
	}
	else
	{
		CRec = RecF(0, 0, 0, 0);
	}
	if (visible == false)
		CRec = RecF(0, 0, 0, 0);
}

void Boss2::Destroy()
{
	HP = 0;
}
