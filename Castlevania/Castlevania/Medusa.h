#pragma once
#include "Enemy.h"

class Medusa :
	public Enemy
{
private:


public:
	Medusa(float x, float y);
	~Medusa();
	void Init(LPDIRECT3DDEVICE9 d3ddv, CSimon* simon, BulletManager* bulletManager, Explosion* explosion);
	void Update();
	void UpdateGunPoint();
	void Draw(int vpx, int vpy);
	void BulletShoot();
	void Destroy();
};

