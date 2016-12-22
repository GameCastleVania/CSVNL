#pragma once
#include "Enemy.h"

class Boss2 :
	public Enemy
{
private:
	Sprite *_Boss2Idle;
	Sprite *_Boss2Move;
	DWORD last_time;
	bool IsReturn = false;
	int temp = 0;
	int _Time = 0, _hitTime = 0;
	int count;
	bool isShooting;
	bool IsChange = false;
	float vxbackup, vybackup;
	
public:
	Boss2(float X, float Y);
	~Boss2();
	void Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon* _simon, BulletManager* _bulletManager, Explosion* _explosion);
	void Update();
	void UpdateGunPoint();
	void Draw(int vpx, int vpy);
	void BulletShoot();
	bool MoveTo(float _x, float _y);
	void UpdateRec();
	void Destroy();
};

