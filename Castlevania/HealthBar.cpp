#include "HealthBar.h"
extern int SimonHP;
HealthBar::HealthBar()
{

}
HealthBar::~HealthBar()
{

}
HealthBar::HealthBar(LPDIRECT3DDEVICE9 _d3ddv, float x, float y, int vpx, int vpy)
{
	healthbar = new Sprite(_d3ddv, "resource\\image\\image\\heal.png", 11, 18, 3, 3);
	simonhealth = SimonHP;
	bosshealth = 16;
	maxhealth = 16;
}

void HealthBar::Update()
{
	simonhealth = SimonHP;
}
void HealthBar::Draw(int vpx, int vpy)
{
	Render(vpx,vpy);
}

void HealthBar::Render(int vpx, int vpy)
{
	for (int i = 0; i < simonhealth; i++)
	{
		healthbar->SetIndex(0);
		healthbar->Render(vpx + 100 + 10 * i,vpy - 40, vpx, vpy);
	}
	for (int j = simonhealth; j < maxhealth; j++)
	{
		healthbar->SetIndex(1);
		healthbar->Render(vpx + 100 + 10 * j, vpy - 40, vpx, vpy);
	}
	for (int i = 0; i < bosshealth; i++)
	{
		healthbar->SetIndex(2);
		healthbar->Render(vpx + 100 + 10 * i, vpy - 70, vpx, vpy);
	}
	for (int i = bosshealth; i < maxhealth; i++)
	{
		healthbar->SetIndex(1);
		healthbar->Render(vpx + 100 + 10 * i, vpy - 70, vpx, vpy);
	}
}