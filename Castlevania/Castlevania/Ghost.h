#pragma once
#include "Enemy.h"

class Ghost :
	public Enemy
{
private:


public:
	Ghost(float x, float y);
	~Ghost();
	void Init(LPDIRECT3DDEVICE9 d3ddv, CSimon* simon, BulletManager* bulletManager, Explosion* explosion);
	void Update();
	void UpdateGunPoint();
	void Draw(int vpx, int vpy);
	void BulletShoot();
	void Destroy();
};

