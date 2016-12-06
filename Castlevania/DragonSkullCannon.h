#pragma once
#include "Enemy.h"

class DragonSkullCannon :
	public Enemy
{
private:


public:
	DragonSkullCannon(float x, float y);
	~DragonSkullCannon();
	void Init(LPDIRECT3DDEVICE9 d3ddv, CSimon* simon, BulletManager* bulletManager, Explosion* explosion);
	void Update();
	void UpdateGunPoint();
	void Draw(int vpx, int vpy);
	void BulletShoot();
	void Destroy();
};

