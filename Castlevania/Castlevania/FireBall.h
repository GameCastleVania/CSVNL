#pragma once
#include "Bullet.h"
#include "utils.h"

class FireBall :
	public Bullet
{
protected:
	Sprite* fireball;
public:
	FireBall();
	FireBall(LPDIRECT3DDEVICE9 d3ddv, Explosion* _explosion);
	~FireBall();

	void Draw(float vpx, float vpy);
	void Update();
	void Destroy();
};

