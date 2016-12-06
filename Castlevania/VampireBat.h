#pragma once
#include "Enemy.h"

class VampireBat :
	public Enemy
{
private:


public:
	VampireBat(float x, float y);
	~VampireBat();
	void Init(LPDIRECT3DDEVICE9 d3ddv, CSimon* simon, BulletManager* bulletManager, Explosion* explosion);
	void Update();
	void UpdateGunPoint();
	void Draw(int vpx, int vpy);
	void BulletShoot();
	void Destroy();
};

