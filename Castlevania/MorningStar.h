#pragma once
#include "simon.h"
#include "weapon.h"

class MorningStar :
	public Weapon
{
protected:
	DWORD last_time;
	CSimon* simon;
	Sprite* mstarL;
	Sprite* mstarR;
public:
	MorningStar();
	MorningStar(LPDIRECT3DDEVICE9 d3ddv, Explosion* _explosion, CSimon* _simon);
	~MorningStar();

	void Draw(float vpx, float vpy);
	void Update();
	void Destroy();
};
