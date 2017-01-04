#include "Boss3.h"


extern int Boss3HP;
Boss3::Boss3()
{
}

Boss3::Boss3(float X, float Y)
{
	PosX = x = X;
	PosY = y = Y + 10;
	LRight = true;
	exploded = false;
	shooting = true;
	wasHit = false;
	hitTime = 0;
	isDead = 0;
	type = 4;
	HP = 16;
	vx = 2;
	vy = 0;
	CRec = RecF(x, y, 32, 80);
}


Boss3::~Boss3()
{
}

void Boss3::Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon * _simon, BulletManager * _bulletManager, Explosion * _explosion)
{
	d3ddv = _d3ddv;
	simon = _simon;
	bulletManager = _bulletManager;
	explosion = _explosion;
	Boss3L = new Sprite(d3ddv, "resource\\image\\boss\\BMap3\\BossLv3left.png", 32, 80, 2, 2);
	Boss3R = new Sprite(d3ddv, "resource\\image\\boss\\BMap3\\BossLv3right.png", 32, 80, 2, 2);
}

void Boss3::Update()
{
	if (stopUpdate == false && _stopUpdate == false)
	{
		Boss3HP = HP;
		float _x = simon->GetX() - 32;
		float _y = simon->GetY() - 32;
		if (_x > 4900) // o giua 2 con booss
		{
			ready = true;
		}
		if (ready)
		{
			if (!wasHit)
			{

				if (!checkDir)
				{
					if (setVel)
					{
						if (x < _x)
							vx = 1.3;
						else
							vx = -1.3;
						setVel = false;
					}

					if (vx > 0 && x > _x || vx < 0 && x < _x)
					{
						checkDir = true;
						setVel = true;
					}
				}
				else
				{
					if (setVel)
					{
						vx = -vx;
						setVel = false;
					}

					_Time++;
					if (_Time > 100 || x > 5100 || x < 4700)
					{
						vx = 0;
						if (_Time > 120)
						{
							checkDir = false;
							setVel = true;
							if (shooting)
							{
								if (LRight)
									BulletShoot(3.0f, 3.1f);
								else
									BulletShoot(-3.0f, 3.1f);
							}
							_Time = 0;
						}
					}
				}
				if (vx > 0)
					LRight = true;
				else
					LRight = false;
				DWORD now = GetTickCount();
				if (now - last_time > 1000 / 5)
				{
					if (!LRight)
						Boss3L->NextRepeat();
					else
						Boss3R->NextRepeat();
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
					Hit = true;
				}
			}

			x += vx;
		}
	}
	if (!exploded && HP <= 0)
	{
		explosion->Get(11, x, y, 7);
		explosion->Get(11, x + 25, y, 7);
		explosion->Get(11, x + 50, y, 7);
		explosion->Get(11, x, y - 25, 7);
		explosion->Get(11, x + 25, y - 25, 7);
		explosion->Get(11, x + 50, y - 25, 7);
		explosion->Get(12, 4800, 132, 7);
		exploded = true;
		visible = false;
		shooting = false;
		ready = false;
	}
	UpdateRec();
}

void Boss3::UpdateGunPoint()
{
}

void Boss3::Draw(int vpx, int vpy)
{
	if (visible)
	{
		if (!exploded)
		{
			if (LRight)
				Boss3R->Render(x + 32, y + 32, vpx, vpy);
			else
				Boss3L->Render(x + 32, y + 32, vpx, vpy);
		}
	}
}

void Boss3::BulletShoot(float _vx, float _vy)
{
	bulletManager->Get(3, x, y, _vx, _vy);
}

void Boss3::UpdateRec()
{
	if (HP > 0)
	{
		CRec = RecF(x, y, 32, 80);
	}
	else
	{
		CRec = RecF(0, 0, 0, 0);
	}
	if (visible == false)
		CRec = RecF(0, 0, 0, 0);
}

void Boss3::Destroy()
{
	HP = 0;
}
