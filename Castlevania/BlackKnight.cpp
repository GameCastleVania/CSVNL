#include "BlackKnight.h"

#define ANIMATE_RATE 1

BlackKnight::BlackKnight()
{}

BlackKnight::BlackKnight(float X, float Y)
{
	x = X;
	y = Y;
	LRight = false;
	exploded = false;
	shooting = false;
	isDead = 0;
	HP = 2;
	CRec = RecF(x, y, 32, 64);
}

void BlackKnight::Init(LPDIRECT3DDEVICE9 D3ddv, CSimon* Simon, BulletManager* BulletManager, Explosion* Explosion)
{
	d3ddv = D3ddv;
	simon = Simon;
	bulletManager = BulletManager;
	explosion = Explosion;
	BKnightL = new Sprite(d3ddv, "resource\\image\\enemy\\EMap2\\1L.png", 32, 64, 4, 4);
	BKnightR = new Sprite(d3ddv, "resource\\image\\enemy\\EMap2\\1R.png", 32, 64, 4, 4);

}

void BlackKnight::Update()
{
	
}

void BlackKnight::Draw(int vpx, int vpy)
{
	
	BKnightL->Render(x + 16, y + 32, vpx, vpy);
}

void BlackKnight::UpdateGunPoint()
{
	
}

void BlackKnight::Destroy()
{
	HP = 0;
}