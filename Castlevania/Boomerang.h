#pragma once
#include "weapon.h"
class Boomerang :
	public Weapon
{
protected:
	Sprite* boomerangL;
	Sprite* boomerangR;
	int life;
public:
	Boomerang();
	Boomerang(LPDIRECT3DDEVICE9 d3ddv, Explosion* _explosion);
	~Boomerang();

	void Draw(float vpx, float vpy);
	void Update();
	void Destroy();
};
