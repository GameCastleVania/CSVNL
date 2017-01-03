#pragma once
#include "Enemy.h"

class Boss3 :
	public Enemy
{
private:
	

public:
	Boss3(float X, float Y);
	~Boss3();
	void Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon* _simon, BulletManager* _bulletManager, Explosion* _explosion);
	void Update();
	void UpdateGunPoint();
	void Draw(int vpx, int vpy);
	void BulletShoot();
	bool MoveTo(float _x, float _y);
	void UpdateRec();
	void Destroy();
};