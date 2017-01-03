#pragma once
#include "Enemy.h"

class Monkey :
	public Enemy
{
private:
	Sprite *MonkeyL;
	Sprite *MonkeyR;
	DWORD last_time;
	int Delta = 0;
	int vxbackup;
public:
	void Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon* _simon, BulletManager* _bulletManager, Explosion* _explosion);
	void Update();
	Monkey();
	Monkey(float x, float y);
	~Monkey();
	void UpdateGunPoint();
	void Draw(int vpx, int vpy);
	void UpdateRect();
	//void BulletShoot();
	void Destroy();
};

