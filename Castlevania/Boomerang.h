#pragma once
#include "weapon.h"
#include "simon.h"

class Boomerang :
	public Weapon
{
protected:
	Sprite* boomerangL;
	Sprite* boomerangR;
	DWORD last_time;
	CSimon* simon;

public:
	Boomerang();
	Boomerang(LPDIRECT3DDEVICE9 d3ddv, Explosion* _explosion, CSimon* _simon);
	~Boomerang();

	void Draw(float vpx, float vpy);
	void Update();
	void Destroy();
};
