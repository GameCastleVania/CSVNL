#pragma once
#include "Enemy.h"

class DownUp :
	public Enemy
{
private:
	Sprite *downup;
	DWORD last_time;

public:
	DownUp();
	DownUp(float x, float y);
	~DownUp();
	void Init(LPDIRECT3DDEVICE9 d3ddv, CSimon* simon, BulletManager* bulletManager, Explosion* explosion);
	void Update();
	void UpdateGunPoint();
	void Draw(int vpx, int vpy);
	//void BulletShoot();
	void Destroy();
};