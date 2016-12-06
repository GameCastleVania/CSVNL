#pragma once
#include "Bullet.h"
#include "explosion.h"

class Boss2Bullet : public Bullet
{
protected:
	Sprite* bullet;
	int animate;
public:
	Boss2Bullet();
	Boss2Bullet(LPDIRECT3DDEVICE9 d3ddv);
	~Boss2Bullet();

	void Draw(float vpx, float vpy);
	void Update();
	void Destroy();
};

