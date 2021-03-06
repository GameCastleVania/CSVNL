#pragma once
#include "Enemy.h"
class Boss3 :
	public Enemy
{
private:
	Sprite *Boss3L;
	Sprite *Boss3R;
	DWORD last_time;
	int _Time = 0, _hitTime = 0;
	bool isShooting;
	bool checkDir = false;
	bool setVel = true;
	bool Hit = true;
	float vxbackup, vybackup;
public:
	Boss3();
	Boss3(float X, float Y);
	~Boss3();
	void Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon* _simon, BulletManager* _bulletManager, Explosion* _explosion);
	void Update();
	void UpdateGunPoint();
	void Draw(int vpx, int vpy);
	void BulletShoot(float _vx, float _vy);
	void UpdateRec();
	void Destroy();
};

