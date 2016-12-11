#pragma once
#include "weapon.h"
#include "simon.h"
#include "utils.h"

class Dagger :
	public Weapon
{
protected:
	Sprite* daggerL;
	Sprite* daggerR;
	DWORD last_time;
	CSimon* simon;

public:
	Dagger();
	Dagger(LPDIRECT3DDEVICE9 d3ddv, Explosion* _explosion, CSimon* _simon);
	~Dagger();

	void Draw(float vpx, float vpy);
	void Update();
	void Destroy();
};
