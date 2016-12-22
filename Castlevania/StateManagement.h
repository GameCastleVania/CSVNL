#pragma once
#include "State.h"
#include "Sound.h"
#include <d3dx9.h>
#include "Keyboard.h"

class StateManagement
{
public:
	static StateManagement* GetInstance()
	{
		if (!s_pIntance)
		{
			s_pIntance = new StateManagement();
		}
		return s_pIntance;
	}
protected:
	static StateManagement* s_pIntance;
protected:
	StateManagement() :m_pCurrentState(0), m_pNextState(0) {}
protected:
	State* m_pCurrentState;
	State* m_pNextState;
public:
	void Update(bool isPause, LPDIRECT3DDEVICE9 d3ddv, DSound* Audio, Keyboard* kbd, int &vpx, int& vpy);
	void SwitchState(State* nextState);
};