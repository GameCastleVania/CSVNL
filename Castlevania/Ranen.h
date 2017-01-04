#pragma once
#include "Enemy.h"

class Raven :
	public Enemy
{
private:
	Sprite *RavenL, *RavenR;
	float _TimeDelay = 0;
	bool isAttack = false;
	DWORD last_time;

public:
	Raven(float X, float Y);
	~Raven();
	void Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon* _simon, BulletManager* _bulletManager, Explosion* _explosion);
	void Update();
	void UpdateGunPoint();
	void Draw(int vpx, int vpy);
	void BulletShoot();
	bool MoveTo(float _x, float _y);
	void UpdateRec();
	void Destroy();
};

