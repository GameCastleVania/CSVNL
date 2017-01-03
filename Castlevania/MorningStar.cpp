#include "MorningStar.h"

#define ANIMATE_RATE 12

MorningStar::MorningStar()
{}


MorningStar::~MorningStar()
{}

MorningStar::MorningStar(LPDIRECT3DDEVICE9 d3ddv, CSimon* _Simon, PSound* _psound, int X, int Y)
{
	psound = _psound;
	simon = _Simon;
	last_time = 0;
	x = X;
	y = Y;
	vx = 0;
	vy = 0;
	fight = false;
	isfightUp = false;
	doFight = false;
	count = 0;

	mstarL = new Sprite(d3ddv, "resource\\image\\weapon\\morningstarL.png", 150, 65, 3, 3);
	mstarR = new Sprite(d3ddv, "resource\\image\\weapon\\morningstarR.png", 150, 65, 3, 3);
	CRec = RecF(0, 0, 150, 65);
}

void MorningStar::Draw(int vpx, int vpy)
{
	if (simon->GetLRight())
	{
		if (fight)
		{
			mstarR->Render(simon->GetX() + 31, simon->GetY(), vpx, vpy);
		}

	}
	else
	{
		if (fight)
			mstarL->Render(simon->GetX() - 31, simon->GetY(), vpx, vpy);
	}
}

void MorningStar::Update(Keyboard *kbd, int vpx, int vpy)
{

	bool fightPress = kbd->IsKeyDown(DIK_RETURN);
	bool fightUp = kbd->IsKeyUp(DIK_RETURN);
	if (fightPress && !fight && isfightUp)
	{
		fight = true;
		isfightUp = false;
		if (mstarL->GetIndex() == 3) mstarL->SetIndex(-1);
		if (mstarR->GetIndex() == 3) mstarR->SetIndex(-1);
	}

	if (fightUp == true)
	{
		isfightUp = true;
	}
	else isfightUp = false;

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{

		if (simon->GetLRight() && fight)
		{
			if (mstarR->GetIndex() == 2)
				Destroy();
			mstarR->NextEnd();

		}

		else if (!simon->GetLRight() && fight)
		{
			if (mstarL->GetIndex() == 2)
				Destroy();
			mstarL->NextEnd();
		}
		last_time = now;
	}
}
void MorningStar::Destroy()
{
	fight = false;

}