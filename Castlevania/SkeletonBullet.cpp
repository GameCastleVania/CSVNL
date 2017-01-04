#include "SkeletonBullet.h"

#define ANIMATE_RATE 10

SkeletonBullet::SkeletonBullet()
{
}

SkeletonBullet::SkeletonBullet(LPDIRECT3DDEVICE9 d3ddv, Explosion * _explosion)
{
	explosion = _explosion;
	fireball = new Sprite(d3ddv, "resource\\image\\enemy\\EMap3\\whitebon.png", 32, 32, 3, 3);
	CRec = RecF(0, 0, 32, 32);
}

SkeletonBullet::~SkeletonBullet()
{
}

void SkeletonBullet::Draw(float vpx, float vpy)
{
	if (visible)
	{
		fireball->Render(x + 7, y + 6, vpx, vpy);
	}
}

void SkeletonBullet::Update()
{
	vy -= 0.1;
	x += vx;
	y += vy;
	CRec.x = x;
	CRec.y = y;
	CRec.vx = vx;
	CRec.vy = vy;
	CRec = RecF(x, y, 32, 32);
	if (visible == false)
		CRec = RecF(0, 0, 0, 0);

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{	
		fireball->NextRepeat();
		last_time = now;

	}
}

void SkeletonBullet::Destroy()
{
	CRec = RecF(0, 0, 0, 0);
	visible = false;
	x = y = vx = vy = -100;
}
