#include "Boss3Bullet.h"



Boss3Bullet::Boss3Bullet()
{
}

Boss3Bullet::Boss3Bullet(LPDIRECT3DDEVICE9 d3ddv)
{
	bulletL = new Sprite(d3ddv, "resource\\image\\boss\\BMap3\\3L.png", 32, 20, 2, 2);
	bulletL = new Sprite(d3ddv, "resource\\image\\boss\\BMap3\\3R.png", 32, 20, 2, 2);
	CRec = RecF(0, 0, 32, 20);
	animate = 0;
}


Boss3Bullet::~Boss3Bullet()
{
}

void Boss3Bullet::Draw(float vpx, float vpy)
{
	if (visible) {
		if (vx < 0)
			bulletL->Render(x + 16, y + 10, vpx, vpy);
		else
			bulletR->Render(x + 16, y + 10, vpx, vpy);
	}
}

void Boss3Bullet::Update()
{
	if (animate > 5)
	{
		if (vx > 0)
			bulletR->Next();
		else
			bulletL->Next();
		animate = 0;
	}
	if (vy > 5)
		isDown = true;
	if (vy < -5)
		isDown = false;

	if (isDown)
		vy -= 0.2;
	else
		vy += 0.2;

	x += vx;
	y += vy;
	CRec.x = x + 16;
	CRec.y = y + 10;
	animate++;

	CRec = RecF(x, y, 32, 20);
	if (visible == false)
		CRec = RecF(0, 0, 0, 0);
}

void Boss3Bullet::Destroy()
{
	visible = false;
	animate = 0;
	CRec = RecF(0, 0, 0, 0);
	x = y = vx = vy = -100;
}
