#pragma once
#include "weapon.h"
#include "simon.h"

class FireBomb :
	public Weapon
{
protected:
	Sprite* fbombL;
	Sprite* fbombR;
	Sprite* fbomb2;
	CSimon* simon;
	DWORD last_time;
	int time = 0;
public:
	FireBomb();
	FireBomb(LPDIRECT3DDEVICE9 d3ddv, Explosion* _explosion, CSimon* _simon);
	~FireBomb();

	void Draw(float vpx, float vpy);
	void Update();
	void Destroy();
};
