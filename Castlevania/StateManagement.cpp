#include "StateManagement.h"

extern int Current_State = 0;
extern bool vpMove = false;
extern int SimonHP = 16;
extern int count2w = 2;

StateManagement* StateManagement::s_pIntance = 0;

void StateManagement::Update(bool isPause, LPDIRECT3DDEVICE9 d3ddv, DSound* Audio, Keyboard* kbd, int &vpx, int &vpy)
{
	// check if need switch state
	if (m_pCurrentState != m_pNextState)
	{
		if (m_pCurrentState)
		{
			m_pCurrentState->Exit(vpx, vpy);
			delete m_pCurrentState;
		}
		if (m_pNextState)
		{
			m_pNextState->Init(d3ddv, Audio, kbd);
		}
		m_pCurrentState = m_pNextState;
	}

	//update state
	if (m_pCurrentState)
	{
		
		m_pCurrentState->Draw(vpx, vpy);
		if (!isPause)
		{
			m_pCurrentState->Update(vpx, vpy);

		}

		


	}
}
void StateManagement::SwitchState(State* nextState)
{

	m_pNextState = nextState;

}