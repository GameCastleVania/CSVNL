#include "Boss2Bullet.h"


Boss2Bullet::Boss2Bullet()
{}

Boss2Bullet::~Boss2Bullet()
{}

Boss2Bullet::Boss2Bullet(LPDIRECT3DDEVICE9 d3ddv)
{
	bullet = new Sprite(d3ddv, "resource\\image\\boss\\BMap2\\2.png", 64, 20, 2, 2);
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
		x += vx;
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
