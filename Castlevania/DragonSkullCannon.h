#pragma once
#include "Enemy.h"

class DragonSkullCannon :
	public Enemy
{
private:
	Sprite *DSkullL;
	Sprite *DSkullR;
	int count;
	bool isShooting;
	bool shootST;

public:
	DragonSkullCannon(float X, float Y);
	~DragonSkullCannon();
	void Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon* _simon, BulletManager* _bulletManager, Explosion* _explosion);
	void Update();
	void UpdateGunPoint();
	void Draw(int vpx, int vpy);
	void BulletShoot();
	void UpdateRect();
	void Destroy();

};

