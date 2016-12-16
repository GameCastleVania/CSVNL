#include "FireBall.h"

FireBall::FireBall()
{}

FireBall::FireBall(LPDIRECT3DDEVICE9 d3ddv, Explosion* _explosion)
{
	explosion = _explosion;
	fireball = new Sprite(d3ddv, "resource\\image\\weapon\\danquai.png", 14, 12, 1, 1);
	CRec = RecF(0, 0, 14, 12);
}

FireBall::~FireBall()
{
}

void FireBall::Draw(float vpx, float vpy)
{
	if (visible)
	{
		fireball->Render(x + 7, y + 6, vpx, vpy);
	}
}

void FireBall::Update()
{
	x += vx;
	y += vy;
	CRec.x = x;
	CRec.y = y;
	CRec.vx = vx;
	CRec.vy = vy;
}

void FireBall::Destroy()
{
	//explosion->Get(0, x, y, 0);
	CRec = RecF(0, 0, 0, 0);
	visible = false;
	x = y = vx = vy = -100;
}