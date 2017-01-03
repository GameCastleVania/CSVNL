#pragma once
#include "State.h"
#include "StateManagement.h"
#include "StateLoad.h"

class StateMap3_1 : public State
{
public:
	StateMap3_1();
	~StateMap3_1();

	void Init(LPDIRECT3DDEVICE9 D3ddv, DSound* Audio, Keyboard* kbd);
	void Update(int &vpx, int &vpy);
	void Draw(int vpx, int vpy);
	void Exit(int &vpx, int &vpy);

	void Render(int vpx, int vpy);
	void ViewPortUpdate(int &vpx, int &vpy);

};

