#pragma once
#include "State.h"
#include "StateLoad.h"
#include "sprite.h"
#include "sound.h"
#include "font.h"
#include "game.h"


class StateMainMenu :
	public State
{
public:
	StateMainMenu();
	~StateMainMenu() {}

	LPDIRECT3DDEVICE9 d3ddv;
	LPDIRECT3DSURFACE9 BackBuffer;
	LPDIRECT3DSURFACE9 Background;
	LPD3DXSPRITE	SpriteHandler;

	void Init(LPDIRECT3DDEVICE9 D3ddv, DSound* Audio, Keyboard* kbd);
	void Update(int &vpx, int &vpy);
	void Draw(int vpx, int vpy);
	void Exit(int &vpx, int &vpy);

private:
	int choise;

	HWND G_hWnd;
	Keyboard* kbd;
	Sprite* background;
	Sprite mainmenu;
	Font *text;

};

