#pragma once
#include "weapon.h"
#include "simon.h"

class Axe :
	public Weapon
{
protected:
	Sprite* axeL;
	Sprite* axeR;
	DWORD last_time;
	CSimon* simon;
	int time = 0;
public:
	Axe();
	Axe(LPDIRECT3DDEVICE9 d3ddv, Explosion* _explosion, CSimon* _simon);
	~Axe();

	void Draw(float vpx, float vpy);
	void Update();
	void Destroy();
};
