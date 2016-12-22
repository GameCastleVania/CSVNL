#include "FireBomb.h"
#define ANIMATE_RATE 8

FireBomb::FireBomb()
{}


FireBomb::~FireBomb()
{}

FireBomb::FireBomb(LPDIRECT3DDEVICE9 d3ddv, Explosion* _explosion, CSimon* _simon)
{
	explosion = _explosion;
	simon = _simon;
	last_time = 0;


	fbombL = new Sprite(d3ddv, "resource\\image\\weapon\\2L.png", 32, 26, 3, 3);
	fbombR = new Sprite(d3ddv, "resource\\image\\weapon\\2R.png", 32, 26, 3, 3);
	fbomb2 = new Sprite(d3ddv, "resource\\image\\weapon\\2L2.png", 32, 26, 2, 2);
	CRec = RecF(0, 0, 32, 26);
}

void FireBomb::Draw(float vpx, float vpy)
{

	if (visible)
	{
		if (y > (simon->GetY() - 27))
		{
			fbombL->SetIndex(0);
			fbombR->SetIndex(0);
			if (simon->GetLRight()) fbombR->Render(x + 12, y, vpx, vpy);
			else if (!simon->GetLRight()) fbombL->Render(x - 12, y, vpx, vpy);
		}
		if (y <= (simon->GetY() - 27))
		{
			fbomb2->Render(x + 10, y + 10, vpx, vpy);

		}
	}
}

void FireBomb::Update()
{
	if (visible)
	{
		if (y > (simon->GetY() - 27))
		{
			if (y > simon->GetY() + 32) falling = true;

			if (falling)
			{
				time++;

				// tao duong cong khi roi xuong
				if (time < 3) {
					y += 3.0f;
					x += vx - 0.5f;
				}
				if (time >= 3 && time <= 6) {
					y += 2.0f;
					x += vx - 0.2;
				}
				if (time > 6 && time <= 9) {
					y += 1.0f;
					x += vx;
				}
				if (time > 9 && time <= 12) {
					y += 0.3f;
					x += vx;
				}
				if (time > 12 && time <= 15) {
					y -= 1.3f;
					x += vx;
				}
				if (time > 15 && time <= 18) {
					y -= 2.3f;
					x += vx;
				}
				if (time > 18) // roi xuong
				{
					x += vx;
					y -= vy;
				}
			}
			else // di len 
			{
				x += (vx + 0.3f);
				y += (vy + 0.7f);
			}
		}
		else
		{
			time++;
			DWORD now = GetTickCount();
			if (now - last_time > 1000 / ANIMATE_RATE)
			{
				fbomb2->Next();
				last_time = now;
			}
			if (time >= 80) Destroy();
		}

		CRec.x = x;
		CRec.y = y;
		CRec.vx = vx;
		CRec.vy = vy;
	}
}
void FireBomb::Destroy()
{
	//explosion->Get(1, x, y, 5);
	falling = false;
	visible = false;
	x = y = -100;
	vx = vy = 0;
	CRec = RecF(0, 0, 0, 0);
}
