#pragma once
#include "Enemy.h"


class Skeleton :
	public Enemy
{
private:
	Sprite *skeleL, *skeleR;
	float _TimeFire = 0;
	bool isFire = false;
	DWORD last_time;

public:
	Skeleton(float X, float Y);
	~Skeleton();
	void Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon* _simon, BulletManager* _bulletManager, Explosion* _explosion);
	void Update();
	void UpdateGunPoint();
	void Draw(int vpx, int vpy);
	void BulletShoot();
	void UpdateRec();
	void Destroy();
};


