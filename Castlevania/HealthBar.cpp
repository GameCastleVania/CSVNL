#include "HealthBar.h"
extern int SimonHP;
extern int Boss2HP;
extern int Boss3HP;
extern int Current_State;
extern int Life_Simon;

HealthBar::HealthBar()
{

}
HealthBar::~HealthBar()
{

}
HealthBar::HealthBar(LPDIRECT3DDEVICE9 _d3ddv, float x, float y, int vpx, int vpy, Keyboard* Kbd)
{
	axeitem = new Sprite(_d3ddv, "resource\\image\\item\\7.png", 30, 28, 1, 1);
	bmritem = new Sprite(_d3ddv, "resource\\image\\item\\8.png", 30, 28, 1, 1);
	daggeritem = new Sprite(_d3ddv, "resource\\image\\item\\4.png", 32, 18, 1, 1);
	fbombitem = new Sprite(_d3ddv, "resource\\image\\item\\9.png", 32, 32, 1, 1);

	healthbar = new Sprite(_d3ddv, "resource\\image\\image\\heal.png", 11, 18, 3, 3);
	simonhealth = SimonHP;
	if (Current_State <= 5)
	bosshealth = Boss2HP;
	else bosshealth = Boss3HP;
	maxhealth = 16;
	kbd = Kbd;
}

void HealthBar::Update()
{
	simonhealth = SimonHP;
	if (Current_State <= 5)
		bosshealth = Boss2HP;
	else bosshealth = Boss3HP;

	/*if (SimonHP <= 0){
		if (Life_Simon == 4) Life_Simon == 3;
		else if (Life_Simon == 3) Life_Simon == 2;
		else if (Life_Simon == 2) Life_Simon == 1;
		else if (Life_Simon == 1) Life_Simon == 0;
	}*/
}
void HealthBar::Draw(int vpx, int vpy)
{
	Render(vpx,vpy);
}

void HealthBar::Render(int vpx, int vpy)
{
	//draw thanh mau boss va mau simon
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

	//draw item
	if (kbd->IsKeyDown(DIK_Z)) {
		Zpress = true;
		Xpress = false;
		Cpress = false;
		Vpress = false;

	}
	if (kbd->IsKeyDown(DIK_X)) {
		Zpress = false;
		Xpress = true;
		Cpress = false;
		Vpress = false;
	}
	if (kbd->IsKeyDown(DIK_C)) {
		Zpress = false;
		Xpress = false;
		Cpress = true;
		Vpress = false;
	}
	if (kbd->IsKeyDown(DIK_V)) {
		Zpress = false;
		Xpress = false;
		Cpress = false;
		Vpress = true;
	}

	if (Zpress)
		fbombitem->Render(vpx + 338, vpy - 50, vpx, vpy);
	else if (Xpress)
		axeitem->Render(vpx + 335, vpy - 50, vpx, vpy);
	else if (Cpress)
		daggeritem->Render(vpx + 335, vpy - 50, vpx, vpy);
	else if (Vpress)
		bmritem->Render(vpx + 337, vpy - 50, vpx, vpy);

}