#pragma once
#include "Enemy.h"

class BX :
	public Enemy
{
private:
	Sprite *BXL;
	Sprite *BXR;
	DWORD last_time;
	int Delta = 0;
	int vxbackup;
public:
	void Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon* _simon, BulletManager* _bulletManager, Explosion* _explosion);
	void Update();
	BX();
	BX(float x, float y);
	~BX();
	void UpdateGunPoint();
	void Draw(int vpx, int vpy);
	void UpdateRect();
	//void BulletShoot();
	void Destroy();
};

