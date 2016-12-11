#pragma once
#include "State.h"
#include "StateMap2_1.h"
#include "sprite.h"
#include "game.h"

class StateLoad :
	public State
{
private:
	float vt;				//toa do X
	Sprite *background;
	Sprite *simonL;
	Sprite *simonB;
	Sprite *helicopter;
	Sprite *bat;
	Sprite *bat1;
	DWORD last_time;
public:
	StateLoad();
	~StateLoad();

	void Init(LPDIRECT3DDEVICE9 D3ddv, DSound* Audio, Keyboard* kbd);
	void Update(int &vpx, int &vpy);
	void Draw(int vpx, int vpy);
	void Exit(int &vpx, int &vpy);
};

