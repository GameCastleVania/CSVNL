#pragma once
#include "Enemy.h"

class VampireBat :
	public Enemy
{
private:
	Sprite *BatLR;
	DWORD last_time;

public:
	VampireBat(float X, float Y);
	~VampireBat();
	void Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon* _simon, BulletManager* _bulletManager, Explosion* _explosion);
	void Update();
	void UpdateGunPoint();
	void Draw(int vpx, int vpy);
	void BulletShoot();
	void UpdateRec();
	void Destroy();
};

