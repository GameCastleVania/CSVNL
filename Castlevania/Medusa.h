#pragma once
#include "Enemy.h"

class Medusa :
	public Enemy
{
private:
	Sprite *MedusaL;
	Sprite *MedusaR;
	DWORD last_time;
public:
	Medusa(float X, float Y);
	~Medusa();
	void Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon* _simon, BulletManager* _bulletManager, Explosion* _explosion);
	void Update();
	void UpdateGunPoint();
	void Draw(int vpx, int vpy);
	void BulletShoot();
	void UpdateRec();
	void Destroy();
};

