#pragma once
#include "weapon.h"
class Axe :
	public Weapon
{
protected:
	Sprite* axeL;
	Sprite* axeR;
	int life;
public:
	Axe();
	Axe(LPDIRECT3DDEVICE9 d3ddv, Explosion* _explosion);
	~Axe();

	void Draw(float vpx, float vpy);
	void Update();
	void Destroy();
};
