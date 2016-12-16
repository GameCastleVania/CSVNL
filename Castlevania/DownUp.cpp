#include "DownUp.h"

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
	HP = 2;
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
		que[i] = new Que(PosX, PosY - 10 * i);
		que[i]->Init(_d3ddv, _simon, _bulletManager, _explosion);
		que[i]->SetVisible(false);
	}
}

void DownUp::Update()
{
	float _x = simon->GetX() - 16;
	float _y = simon->GetY() - 32;
	float delta = sqrtf((_x - x)*(_x - x) + (_y - y)*(_y - y));
	if (delta < 300)
		ready = true;
	if (ready)
	{
		visible = true;
		_Time++;
		if (_Time > 200)
		{
			vy = -2;
			isDown = true;
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
			downup->Render(x + 16, y + 32, vpx, vpy);
		}
		for (int i = 0; i < 10; i++)
			if (que[i]->GetVisible() == true)
				que[i]->Draw(vpx, vpy);
	}
}

void DownUp::Destroy()
{
}
