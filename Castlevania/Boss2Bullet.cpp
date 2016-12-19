#include "Boss2Bullet.h"


Boss2Bullet::Boss2Bullet()
{}

Boss2Bullet::~Boss2Bullet()
{}

Boss2Bullet::Boss2Bullet(LPDIRECT3DDEVICE9 d3ddv)
{
	bullet = new Sprite(d3ddv, "resource\\image\\boss\\BMap2\\2.png", 64, 20, 1, 1);
	CRec = RecF(0, 0, 32, 10);
	animate = 0;
}

void Boss2Bullet::Draw(float vpx, float vpy)
{
	if (visible){
		bullet->Render(x + 16, y + 10, vpx, vpy);
	}
}
void Boss2Bullet::Update()
{
	if (visible){
		if (animate > 5)
		{
			bullet->Next();
			animate = 0;
		}
		if (PosY > 100 && !isRun)
		{
			vy = -3;
			if (y < 100)
			{
				y = 100;
				vy = 0;
				isRun = true;
			}
		}
		if (PosY < 100 && !isRun)
		{
			vy = 3;
			if (y > 100)
			{
				y = 100;
				vy = 0;
				isRun = true;
			}
		}
		
		if (isRun)
			x += vx;
		if (x > 400)
		{
			vx = 0;
			vy = -2;
		}
		y += vy;
		CRec.x = x + 16;
		CRec.y = y + 10;
	}
	animate++;
}

void Boss2Bullet::Destroy()
{
	visible = false;
	animate = 0;
	CRec = RecF(0, 0, 0, 0);
	x = y = vx = vy = -100;
}
