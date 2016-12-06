#pragma once
#include "Enemy.h"

class BlackKnight :
	public Enemy
{
private:
	Sprite *BKnightL;
	Sprite *BKnightR;
	DWORD last_time;

public:
	BlackKnight();
	BlackKnight(float x, float y);
	~BlackKnight();
	void Init(LPDIRECT3DDEVICE9 d3ddv, CSimon* simon, BulletManager* bulletManager, Explosion* explosion);
	void Update();
	void UpdateGunPoint();
	void Draw(int vpx, int vpy);
	//void BulletShoot();
	void Destroy();
};

