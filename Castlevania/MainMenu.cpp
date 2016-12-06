#include "MainMenu.h"

extern int Current_State;

StateMainMenu::StateMainMenu() {}


void StateMainMenu::Init(LPDIRECT3DDEVICE9 D3ddv, DSound* Audio, Keyboard* kbd)
{
	choise = 0;
	d3ddv = D3ddv;
	this->kbd = kbd;
	psound = new PSound(Audio);
	text = new Font(d3ddv, 25, WINDOW_WIDTH, WINDOW_HEIGHT);
	background = new Sprite(d3ddv, "resource\\image\\image\\mainmenu.png", 514, 450, 1, 1);
}

void StateMainMenu::Draw(int vpx, int vpy)
{
	d3ddv->BeginScene();
	d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 0.0f, 0);
	//ve background
	background->Render(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, vpx, vpy);
	//
	if (choise > 0)// neu nhan enter thi load text nhap nhay
		text->renderAnimation("P U S H   S T A R T   K E Y", 155, 280, 5);
	else 
		text->render("P U S H   S T A R T   K E Y", 155, 280);

	d3ddv->EndScene();
	d3ddv->Present(NULL, NULL, NULL, NULL);
}



void StateMainMenu::Update(int &vpx, int &vpy)
{
	if (kbd->IsKeyDown(DIK_RETURN)) choise = 100;
	else if (kbd->IsKeyDown(DIK_ESCAPE)) PostMessage(G_hWnd, WM_QUIT, 0, 0);

	//thoi gian text nhap nhay de chuyen qua state tiep theo
	choise--;
	if (choise == 0) StateManagement::GetInstance()->SwitchState(new StateLoad());
}

void StateMainMenu::Exit(int &vpx, int &vpy)
{
	Current_State = 1;
	delete(background);
	delete(psound);
}