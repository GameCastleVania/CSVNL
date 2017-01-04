#pragma once
#include "Bullet.h"
class Boss3Bullet :
	public Bullet
{
	Sprite* bulletL, * bulletR;
	int animate;
	bool isDown = true;
public:
	Boss3Bullet();
	Boss3Bullet(LPDIRECT3DDEVICE9 d3ddv);
	~Boss3Bullet();

	void Draw(float vpx, float vpy);
	void Update();
	void Destroy();
};

