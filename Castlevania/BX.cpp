#include "BX.h"
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
BX::BX()
{}

BX::BX(float X, float Y)
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

BX::~BX()
{
}

void BX::Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon* _simon, BulletManager* _bulletManager, Explosion* _explosion)
{
	d3ddv = _d3ddv;
	simon = _simon;
	bulletManager = _bulletManager;
	explosion = _explosion;
	BXL = new Sprite(d3ddv, "resource\\image\\enemy\\EMap3\\BXleft.png", 32, 64, 2, 2);
	BXR = new Sprite(d3ddv, "resource\\image\\enemy\\EMap3\\BXright.png", 32, 64, 2, 2);

}

void BX::Update()
{


	UpdateRect();
	//DBOUT("The value of x is " << type << endl);
}

void BX::Draw(int vpx, int vpy)
{
	if (visible)
	{
		if (!exploded)
		{
			if (!LRight)
				BXL->Render(x + 16, y + 32, vpx, vpy);
			else
				BXR->Render(x + 16, y + 32, vpx, vpy);
		}
	}
}

void BX::UpdateRect()
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

void BX::UpdateGunPoint()
{

}

void BX::Destroy()
{
	HP = 0;
}