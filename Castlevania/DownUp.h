#pragma once
#include "Enemy.h"
#include "Que.h"
class DownUp :
	public Enemy
{
private:
	Sprite *downup;
	DWORD last_time;
	int _Time = 0;
	Que *que[10];
	int count = -1;
	bool isUp = false;
	bool isDown = false;

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