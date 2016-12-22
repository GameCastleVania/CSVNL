#pragma once
#include "Enemy.h"

class Ghost :
	public Enemy
{
private:
	Sprite *ghostL;
	Sprite *ghostR;
	DWORD last_time;
	int vxbackup;
	int vybackup;
public:
	Ghost(float X, float Y);
	~Ghost();
	void Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon* _simon, BulletManager* _bulletManager, Explosion* _explosion);
	void Update();
	void UpdateGunPoint();
	void Draw(int vpx, int vpy);
	void BulletShoot();
	void UpdateRec();
	void Destroy();
};

