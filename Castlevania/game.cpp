#include "Game.h"

Game* Game::pInstance = NULL;

Game::Game(HINSTANCE HInstance, char *Name, int FrameRate)
{
	d3d = NULL;
	d3ddv = NULL;
	backBuffer = NULL;

	name = Name;
	frameRate = FrameRate;
	hInstance = HInstance;
}

Game::~Game()
{
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
}

void Game::Init()
{
	InitWindow();
	InitDirectX();
	InitVariables();
	InitState();
}

void Game::InitVariables()
{
	///////////////////////////////////////////////
	//        Game element constructor
	kbd = new Keyboard(hInstance, hWnd);
	audio = new DSound(hWnd);
	vpx = 0;
	vpy =480;
	///////////////////////////////////
}

void Game::InitState()
{
	StateManagement::GetInstance()->SwitchState(new StateMap2_1());
}

void Game::Run()
{
	MSG msg;
	int done = 0;
	DWORD frame_start = GetTickCount();;

	DWORD tick_per_frame = 100 / frameRate;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();
		DeltaTime = now - frame_start;
		if (DeltaTime >= tick_per_frame)
		{
			kbd->UpdateKeyboard();
			frame_start = now;
			StateManagement::GetInstance()->Update(false, d3ddv, audio, kbd, vpx, vpy);
		}
	}
}


