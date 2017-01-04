#pragma once
#include "Enemy.h"

class Fleamen :
	public Enemy
{
private:
	Sprite *FleamenL;
	Sprite *FleamenR;
	bool isJump = false;
	bool isDelay = true;
	bool isFirst = true;
	float _TimeDelay = 0;
	DWORD last_time;
public:
	Fleamen(float X, float Y);
	~Fleamen();
	void Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon* _simon, BulletManager* _bulletManager, Explosion* _explosion);
	void Update();
	void UpdateGunPoint();
	void Draw(int vpx, int vpy);
	void BulletShoot();
	void UpdateRec();
	void Destroy();
};