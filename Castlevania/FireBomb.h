#pragma once
#include "weapon.h"
class FireBomb :
	public Weapon
{
protected:
	Sprite* fbombL;
	Sprite* fbombR;
	int life;
public:
	FireBomb();
	FireBomb(LPDIRECT3DDEVICE9 d3ddv, Explosion* _explosion);
	~FireBomb();

	void Draw(float vpx, float vpy);
	void Update();
	void Destroy();
};
