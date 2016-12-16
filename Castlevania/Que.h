#pragma once
#include "Enemy.h"
class Que :
	public Enemy
{
private:
	Sprite *cay;
	DWORD last_time;
	float _Time = 0;

public:
	Que();
	Que(float x, float y);
	~Que();
	void Init(LPDIRECT3DDEVICE9 _d3ddv, CSimon* _simon, BulletManager* _bulletManager, Explosion* _explosion);
	void Update();
	void UpdateGunPoint();
	void Draw(int vpx, int vpy);
	void SetVisible(bool vis)
	{
		this->visible = vis;
	}
	//void BulletShoot();
	void Destroy();
};

