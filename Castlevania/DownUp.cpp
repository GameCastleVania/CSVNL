#include "DownUp.h"

#include <iostream>
#include <sstream>
#define ANIMATE_RATE 2
#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}

DownUp::DownUp()
{
}

DownUp::DownUp(float X, float Y)
{
	PosX = x = X;
	PosY = y = Y;
	LRight = true;
	exploded = false;
	shooting = false;
	isDead = 0;
	vx = 0;
	vy = 0;
	CRec = RecF(x, y, 64, 36);
}

DownUp::~DownUp()
{
}

void DownUp::Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon * _simon, BulletManager * _bulletManager, Explosion * _explosion)
{
	d3ddv = _d3ddv;
	simon = _simon;
	bulletManager = _bulletManager;
	explosion = _explosion;
	downup = new Sprite(d3ddv, "resource\\image\\enemy\\EMap2\\7.png", 64, 36, 1, 1);
	for (int i = 0; i < 10; i++)
	{
		que[i] = new Que(PosX + 25, PosY - 10 * i);
		que[i]->Init(_d3ddv, _simon, _bulletManager, _explosion);
		que[i]->SetVisible(false);
	}
}

void DownUp::Update()
{
	float _x = simon->GetX() - 32;
	float _y = simon->GetY() - 16;
	float delta = sqrtf((_x - x)*(_x - x) + (_y - y)*(_y - y));
	//DBOUT(_x << " " << endl);
	if (delta < 800)
		ready = true;
	if (ready)
	{
		visible = true;
		_Time++;
		if (_Time > 70)
		{
			vy = -2;
			isDown = true;
			if (PosX > 800 && PosX < 900)
			{
				if (y < PosY - 60)
				{
					vy = 2;
					_Time = 0;
					isDown = false;
				}
			}
			if (y < PosY - 100)
			{
				vy = 2;
				_Time = 0;
				isDown = false;
			}
		}
		if (y >= PosY && !isDown)
			vy = 0;
		if ((int)(PosY - y) % 20 > 15 && vy > 0)
		{
			if (count >= 0)
			{
				que[count]->SetVisible(false);
				count--;
			}
		}
		if ((int)(PosY - y) % 20 > 15 && vy < 0)
		{
			count++;
			que[count]->SetVisible(true);
		}

		y += vy;
	}
}

void DownUp::UpdateGunPoint()
{
}

void DownUp::Draw(int vpx, int vpy)
{
	if (visible)
	{
		if (!exploded)
		{
			downup->Render(x + 32, y + 16, vpx, vpy);
		}
		for (int i = 0; i < 10; i++)
			if (que[i]->GetVisible() == true)
				que[i]->Draw(vpx, vpy);
	}
}

void DownUp::Destroy()
{
}
