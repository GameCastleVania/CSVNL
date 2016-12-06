#pragma once
#include "weapon.h"
class Dagger :
	public Weapon
{
protected:
	Sprite* daggerL;
	Sprite* daggerR;
	int life;
public:
	Dagger();
	Dagger(LPDIRECT3DDEVICE9 d3ddv, Explosion* _explosion);
	~Dagger();

	void Draw(float vpx, float vpy);
	void Update();
	void Destroy();
};
