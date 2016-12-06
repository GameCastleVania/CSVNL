#pragma once
#include "weapon.h"
class MorningStar :
	public Weapon
{
protected:
	Sprite* mstarL;
	Sprite* mstarR;
	int life;
public:
	MorningStar();
	MorningStar(LPDIRECT3DDEVICE9 d3ddv, Explosion* _explosion);
	~MorningStar();

	void Draw(float vpx, float vpy);
	void Update();
	void Destroy();
};
