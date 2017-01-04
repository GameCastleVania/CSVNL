#include "BlackKnight.h"
#include <iostream>
#include <sstream>

extern int stopUpdate;
extern int Current_State;
#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}
#define ANIMATE_RATE 5
BlackKnight::BlackKnight()
{}

BlackKnight::BlackKnight(float X, float Y)
{
	PosX = x = X;
	PosY = y = Y;
	LRight = true;
	exploded = false;
	shooting = false;
	wasHit = false;
	hitTime = 0;
	type = 4;
	isDead = 0;
	HP = 2;
	vx = 1.2;
	vy = 0;
	CRec = RecF(x, y, 32, 64);
}

BlackKnight::~BlackKnight()
{
}

void BlackKnight::Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon* _simon, BulletManager* _bulletManager, Explosion* _explosion)
{
	d3ddv = _d3ddv;
	simon = _simon;
	bulletManager = _bulletManager;
	explosion = _explosion;
	BKnightL = new Sprite(d3ddv, "resource\\image\\enemy\\EMap2\\1L.png", 32, 64, 4, 4);
	BKnightR = new Sprite(d3ddv, "resource\\image\\enemy\\EMap2\\1R.png", 32, 64, 4, 4);

}

void BlackKnight::Update()
{
	if (_stopUpdate == false && stopUpdate == false) 
	{
		float _x = simon->GetX() - 16;
		float _y = simon->GetY() - 32;
		float kc = sqrtf((_x - x)*(_x - x) + (_y - y)*(_y - y));
		if (kc < 300)
			ready = true;
		if (ready)
		{
			Delta = 120;
			visible = true;
			switch (Current_State)
			{
			case 2:
				Delta = 110;
				break;
			case 3:
				if (PosY < 95)
					Delta = 15;
				else
					if (PosX > 1000)
						Delta = 40;
					else
						Delta = 130;
				break;
			case 4:
				if (PosY < 200)
					Delta = 150;
				else
					Delta = 80;
				break;
			}
			if (wasHit)
			{

				if (vx != 0)
					vxbackup = vx;
				vx = 0;
				hitTime++;
				if (hitTime > 30)
				{
					hitTime = 0;
					vx = vxbackup;
					wasHit = false;
				}
			}
			else
			{
				if (x <= PosX - Delta)
				{
					vx = 1.2;
					LRight = true;
				}
				if (x >= PosX + Delta)
				{
					vx = -1.2;
					LRight = false;
				}

				DWORD now = GetTickCount();
				if (now - last_time > 1000 / ANIMATE_RATE)
				{
					if (LRight)
					{
						BKnightR->NextRepeat();
					}
					else
					{
						BKnightL->NextRepeat();
					}
					last_time = now;
				}
			}
			x += vx;
		}
	}
	if (!exploded && HP <= 0)
	{
		explosion->Get(1, x + 18, y + 34, 7);
		exploded = true;
		visible = false;
		shooting = false;
	}
	UpdateRect();
	//DBOUT("The value of x is " << type << endl);
}

void BlackKnight::Draw(int vpx, int vpy)
{
	if (visible)
	{
		if (!exploded)
		{
			if (!LRight)
				BKnightL->Render(x + 16, y + 32, vpx, vpy);
			else
				BKnightR->Render(x + 16, y + 32, vpx, vpy);
		}
	}
}

void BlackKnight::UpdateRect()
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

void BlackKnight::UpdateGunPoint()
{

}

void BlackKnight::Destroy()
{
	HP = 0;
}