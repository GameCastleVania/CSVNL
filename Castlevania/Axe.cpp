#include "Axe.h"
#define ANIMATE_RATE 8

Axe::Axe()
{}


Axe::~Axe()
{}

Axe::Axe(LPDIRECT3DDEVICE9 d3ddv, Explosion* _explosion, CSimon* _simon)
{
	explosion = _explosion;
	simon = _simon;
	last_time = 0;

	axeL = new Sprite(d3ddv, "resource\\image\\weapon\\3L.png", 30, 28, 4, 4);
	axeR = new Sprite(d3ddv, "resource\\image\\weapon\\3R.png", 30, 28, 4, 4);

	CRec = RecF(0, 0, 30, 28);
}

void Axe::Draw(float vpx, float vpy)
{
	if (fight)
	{
		if (simon->GetLRight()) axeR->Render(x + 15, y, vpx, vpy);
		else if (!simon->GetLRight()) axeL->Render(x - 15, y, vpx, vpy);			
	}	
}

void Axe::Update()
{
		if (y > simon->GetY() + 120) falling = true; 
		
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
				x += vx ;
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

		DWORD now = GetTickCount();
		if (now - last_time > 1000 / ANIMATE_RATE)
		{

			if (simon->GetLRight())
			{
				axeR->Next();

			}

			else if (!simon->GetLRight())
			{
				axeL->Next();
			}
			last_time = now;
		}
		
		CRec.x = x;
		CRec.y = y;
		CRec.vx = vx;
		CRec.vy = vy;
}
void Axe::Destroy()
{
	//explosion->Get(1, x, y, 5);
	fight = false;
	falling = false;
	x = y = -100;
	vx = vy = 0;
	CRec = RecF(0, 0, 0, 0);
}
