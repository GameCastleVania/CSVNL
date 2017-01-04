#pragma once
#include "State.h"
#include "StateManagement.h"
#include "StateLoad.h"
#include "font.h"

class StateMap2_4 : public State
{
public:
	StateMap2_4();
	~StateMap2_4();
	int time = 0;
	void Init(LPDIRECT3DDEVICE9 D3ddv, DSound* Audio, Keyboard* kbd);
	void Update(int &vpx, int &vpy);
	void Draw(int vpx, int vpy);
	void Exit(int &vpx, int &vpy);

	void Render(int vpx, int vpy);
	void ViewPortUpdate(int &vpx, int &vpy);
private:

	Font *text;
};

