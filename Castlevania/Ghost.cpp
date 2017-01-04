#include "Ghost.h"
#include <iostream>
#include <sstream>
#define ANIMATE_RATE 2
#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}

extern int Current_State;
Ghost::Ghost(float X, float Y)
{
	PosX = x = X;
	PosY = y = Y;
	LRight = true;
	exploded = false;
	shooting = false;
	wasHit = false;
	visible = false;
	hitTime = 0;
	isDead = 0;
	type = 4;
	HP = 2;
	vx = 0;
	vy = 0;
	CRec = RecF(x, y, 28, 28);
}

Ghost::~Ghost()
{
}

void Ghost::Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon * _simon, BulletManager * _bulletManager, Explosion * _explosion)
{
	d3ddv = _d3ddv;
	simon = _simon;
	bulletManager = _bulletManager;
	explosion = _explosion;
	ghostL = new Sprite(d3ddv, "resource\\image\\enemy\\EMap2\\3L.png", 28, 28, 2, 2);
	ghostR = new Sprite(d3ddv, "resource\\image\\enemy\\EMap2\\3R.png", 28, 28, 2, 2);
}

void Ghost::Update()
{
	if (_stopUpdate == false && stopUpdate == false)
	{
		float _x = simon->GetX() - 14;
		float _y = simon->GetY() - 14;
		float delta = sqrtf((_x - x)*(_x - x) + (_y - y)*(_y - y));
		DBOUT("Value " << _x << " " << _y << " " << delta << endl);
		switch (Current_State)
		{
		case 4:
			if (PosY < 200)
			{
				if (_x - PosX < -250) //&& _y > 315 && _x > 1500 )
					ready = true;
			}
			else
				if (PosX - _x < -250 && _y > 285 && _x < 1500)
					ready = true;
			break;
		default:
			break;
		}

		if (ready)
		{
			visible = true;
			if (wasHit)
			{

				if (vx != 0)
					vxbackup = vx;
				if (vy != 0)
					vybackup = vy;
				vx = 0;
				vy = 0;
				hitTime++;
				if (hitTime > 10)
				{
					hitTime = 0;
					vx = vxbackup;
					vy = vybackup;
					wasHit = false;
				}
			}
			else
			{
				vx = (_x - x) / delta * 1.2;
				vy = (_y - y) / delta * 1.2;
				if (vx > 0)
					LRight = true;
				if (vx < 0)
					LRight = false;

				x += vx;
				y += vy;
				DWORD now = GetTickCount();
				if (now - last_time > 1000 / ANIMATE_RATE)
				{
					if (!LRight)
						ghostL->NextRepeat();
					else
						ghostR->NextRepeat();
					last_time = now;
				}
			}
		}
	}
	if ((!exploded && HP <= 0))
	{
		explosion->Get(1, x + 14, y + 14, 7);
		exploded = true;
		visible = false;
		shooting = false;
	}
	UpdateRec();
}

void Ghost::UpdateGunPoint()
{
}

void Ghost::Draw(int vpx, int vpy)
{
	if (visible)
	{
		if (!exploded)
		{
			if (!LRight)
				ghostL->Render(x + 14, y + 14, vpx, vpy);
			else
				ghostR->Render(x + 14, y + 14, vpx, vpy);
		}
	}
}

void Ghost::BulletShoot()
{
}

void Ghost::UpdateRec()
{
	if (HP > 0)
	{
		CRec = RecF(x, y, 28, 28);
	}
	else
	{
		CRec = RecF(0, 0, 0, 0);
	}
	if (visible == false)
		CRec = RecF(0, 0, 0, 0);
}

void Ghost::Destroy()
{
	HP = 0;
}
