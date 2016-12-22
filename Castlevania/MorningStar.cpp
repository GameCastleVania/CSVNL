#include "MorningStar.h"

#define ANIMATE_RATE 8

MorningStar::MorningStar()
{}


MorningStar::~MorningStar()
{}

MorningStar::MorningStar(LPDIRECT3DDEVICE9 d3ddv, Explosion* _explosion, CSimon* _simon)
{
	explosion = _explosion;
	simon = _simon;
	last_time = 0;
	mstarL = new Sprite(d3ddv, "resource\\image\\weapon\\morningstarL.png", 150, 65, 3, 3);
	mstarR = new Sprite(d3ddv, "resource\\image\\weapon\\morningstarR.png", 150, 65, 3, 3);
	CRec = RecF(0, 0, 150, 65);
}

void MorningStar::Draw(float vpx, float vpy)
{
	if (visible)
	{
		if (simon->GetLRight()) mstarR->Render(x, y, vpx, vpy);
		else if (!simon->GetLRight()) mstarL->Render(x, y, vpx, vpy);

	}
}

void MorningStar::Update()
{


	if (visible)
	{

		if (simon->GetLRight()){
			x = simon->GetX() + 31;
			y = simon->GetY();
		}
		else{
			x = simon->GetX() - 31;
			y = simon->GetY();
		}


		if (mstarL->GetIndex() == 3) mstarL->SetIndex(-1);
		if (mstarR->GetIndex() == 3) mstarR->SetIndex(-1);

		DWORD now = GetTickCount();
		if (now - last_time > 1000 / ANIMATE_RATE)
		{

			if (simon->GetLRight() && visible)
			{
				if (mstarR->GetIndex() == 2)
					Destroy();
				mstarR->NextEnd();

			}

			else if (!simon->GetLRight() && visible)
			{
				if (mstarL->GetIndex() == 2)
					Destroy();
				mstarL->NextEnd();
			}
			last_time = now;
		}

		CRec = RecF(x, y, 150, 65);

	}
}
void MorningStar::Destroy()
{
	//explosion->Get(1, x, y, 5);
	visible = false;
	CRec = RecF(0, 0, 0, 0);
	x = y = -100;
	vx = vy = 0;
}
