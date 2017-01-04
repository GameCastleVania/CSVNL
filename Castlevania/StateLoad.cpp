#include "StateLoad.h"

extern int Current_State;
#define ANIMATE_RATE_SIMON 5
#define ANIMATE_RATE_BAT 9

StateLoad::StateLoad()
{	
}


StateLoad::~StateLoad()
{
}


void StateLoad::Init(LPDIRECT3DDEVICE9 D3ddv, DSound* Audio, Keyboard* Kbd)
{
	vt = WINDOW_WIDTH; 
	d3ddv = D3ddv;
	kbd = Kbd;
	psound = new PSound(Audio);
	background = new Sprite(d3ddv, "resource\\image\\image\\intro.png", 512, 448,1,1);
	simonL = new Sprite(d3ddv, "resource\\image\\simon\\simon-left.png", 60, 66, 4, 4);
	simonB = new Sprite(d3ddv, "resource\\image\\simon\\simon-Stand.png", 51, 66, 1, 1);
	helicopter = new Sprite(d3ddv, "resource\\image\\image\\helicopter.png", 64, 28, 1, 1);
	bat = new Sprite(d3ddv, "resource\\image\\image\\bat.png", 16, 16, 2, 2);
	bat1 = new Sprite(d3ddv, "resource\\image\\image\\bat.png", 16, 16, 2, 2);
}

void StateLoad::Update(int &vpx, int &vpy)
{
	//xet vi tri x,y de sprite di chuyen
	if (vt > (WINDOW_WIDTH / 2))
	{
		simonL->setX(simonL->getX() - 0.95f);
	}
	bat->setX(bat->getX() + 0.3f);
	bat->setY(bat->getY() + 0.2f);

	bat1->setX(bat1->getX() - 0.2f);
	bat1->setY(bat1->getY() + 0.1f);

	helicopter->setX((helicopter->getX()-0.3f));

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE_SIMON)
	{		
		if (vt > WINDOW_WIDTH / 2)			
			simonL->Next();		
		else
			simonB->Next();		
		last_time = now;
	}
	if (now - last_time > 1000 / ANIMATE_RATE_BAT)
	{
		bat->Next();
		bat1->Next();
	}
	
	if (vt < 200)	//dung khoang time (WINDOW_WIDTH/2) den 200 sau do chuyen map
	{
		StateManagement::GetInstance()->SwitchState(new StateMap2_1());
	}
		

}

void StateLoad::Draw(int vpx, int vpy)
{
	d3ddv->BeginScene();
	d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 0.0f, 0);

	background->Render(514 / 2, 480 / 2, vpx, vpy);	
	if (vt >= WINDOW_WIDTH)//load vi tri ban dau cua sprite
	{
		simonL->Render(500, 94, vpx, vpy);
		bat->Render(100, 320, vpx, vpy);
		bat1->Render(300, 350, vpx, vpy);
		helicopter->Render(514 - 65, 300, vpx, vpy);		
	}
	else if (vt > (WINDOW_WIDTH / 2) && vt < WINDOW_WIDTH) // di chuyen den giua man hinh
	{
		simonL->Render(simonL->getX(), simonL->getY(), vpx, vpy);
		bat->Render(bat->getX(), bat->getY(), vpx, vpy);
		bat1->Render(bat1->getX(), bat1->getY(), vpx, vpy);
		helicopter->Render(helicopter->getX(), helicopter->getY(), vpx, vpy);
	}
	else 
	{
		simonB->Render(simonL->getX(), simonL->getY(), vpx, vpy);
		bat->Render(bat->getX(), bat->getY(), vpx, vpy);
		bat1->Render(bat1->getX(), bat1->getY(), vpx, vpy);
		helicopter->Render(helicopter->getX(), helicopter->getY(), vpx, vpy);
	}
	vt-= 1;
	d3ddv->EndScene();
	d3ddv->Present(NULL, NULL, NULL, NULL);
	
}

void StateLoad::Exit(int &vpx, int &vpy)
{
	Current_State = 2;
	vpx = 0;
	vpy = 480;
	delete(helicopter);
	delete(bat);
	delete(simonB);
	delete(simonL);
	delete(psound);
}