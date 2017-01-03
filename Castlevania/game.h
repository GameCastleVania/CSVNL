#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include "sound.h"
#include "keyboard.h"
#include "MainMenu.h"
#include "StateManagement.h"
//test
#include "StateMap2_1.h"
#include "StateMap2_2.h"
#include "StateMap2_3.h"
#include "StateMap2_4.h"
#include "StateMap3_1.h"
#include "StateMap3_2.h"
#include "StateMap3_3.h"


#define WINDOW_WIDTH 514
#define WINDOW_HEIGHT 480

class Game
{
protected:
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddv;
	LPDIRECT3DSURFACE9 backBuffer;

	HINSTANCE hInstance;
	HWND hWnd;
	DWORD DeltaTime;
	char *name;
	DSound* audio;
	Keyboard* kbd;
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void InitWindow();
	void InitDirectX();
	void InitVariables();
	void InitState();

	////////////////////////////////////////////////////////////////
	//          External Variables
	int vpx, vpy;

	////////////////////////////////////////////////////////////////


public:
	int frameRate;

	Game(HINSTANCE hInstance, char *Name, int FrameRate);
	~Game();
	static Game* GetInstance() { return pInstance; }

	void Init();
	void Run();
	void Pause();
	void Resume();
	void Exit();

private:
	////////////////////////////////////////////////////////////////
	//           GameFuncion
	static Game* pInstance;

	////////////////////////////////////////////////////////////////
};

