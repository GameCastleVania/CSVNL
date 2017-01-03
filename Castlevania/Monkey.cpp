#include "Monkey.h"
#include <iostream>
#include <sstream>

extern int Current_State;
#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}
#define ANIMATE_RATE 5
Monkey::Monkey()
{}

Monkey::Monkey(float X, float Y)
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

Monkey::~Monkey()
{
}

void Monkey::Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon* _simon, BulletManager* _bulletManager, Explosion* _explosion)
{
	d3ddv = _d3ddv;
	simon = _simon;
	bulletManager = _bulletManager;
	explosion = _explosion;
	MonkeyL = new Sprite(d3ddv, "resource\\image\\enemy\\EMap3\\Monkeyleft.png", 32, 32, 2, 2);
	MonkeyR = new Sprite(d3ddv, "resource\\image\\enemy\\EMap3\\Monkeyright.png", 32, 32, 2, 2);

}

void Monkey::Update()
{

	
	UpdateRect();
	//DBOUT("The value of x is " << type << endl);
}

void Monkey::Draw(int vpx, int vpy)
{
	if (visible)
	{
		if (!exploded)
		{
			if (!LRight)
				MonkeyL->Render(x + 16, y + 16, vpx, vpy);
			else
				MonkeyR->Render(x + 16, y + 16, vpx, vpy);
		}
	}
}

void Monkey::UpdateRect()
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

void Monkey::UpdateGunPoint()
{

}

void Monkey::Destroy()
{
	HP = 0;
}