#pragma once
#include "simon.h"


class MorningStar :
	public GameObject
{
private:
	PSound* psound;
	DWORD last_time;
	CSimon* simon;
	Sprite* mstarL;
	Sprite* mstarR;
	bool doFight;
	bool isfightUp;
	int count;
public:
	MorningStar();
	MorningStar(LPDIRECT3DDEVICE9 d3ddv, CSimon* _Simon, PSound* _psound, int X, int Y);
	~MorningStar();
	bool fight;
	void Draw(int vpx, int vpy);
	void Update(Keyboard *kbd, int vpx, int vpy);
	void UpdateRect();
	void Destroy();
};