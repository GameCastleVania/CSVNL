#pragma once
#include "Enemy.h"

class BlackKnight :
	public Enemy
{
private:
	Sprite *BKnightL;
	Sprite *BKnightR;
	DWORD last_time;
	int Delta = 0;
	int vxbackup;
public:
	void Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon* _simon, BulletManager* _bulletManager, Explosion* _explosion);
	void Update();
	BlackKnight();
	BlackKnight(float x, float y);
	~BlackKnight();
	void UpdateGunPoint();
	void Draw(int vpx, int vpy);
	void UpdateRect();
	//void BulletShoot();
	void Destroy();
};

