#pragma once
#include "Bullet.h"
class SkeletonBullet :
	public Bullet
{
protected:
	Sprite* fireball;
	DWORD last_time = 0;
public:
	SkeletonBullet();
	SkeletonBullet(LPDIRECT3DDEVICE9 d3ddv, Explosion* _explosion);
	~SkeletonBullet();

	void Draw(float vpx, float vpy);
	void Update();
	void Destroy();
};

