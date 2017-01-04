#pragma once
#include "Enemy.h"
#include "font.h"
#include <cstdlib>
#include <ctime>

class Candle :
	public Enemy
{
private:
	Sprite *candle;
	DWORD last_time;
	Font* text;
	char* _score;

public:
	Candle();
	Candle(float x, float y);
	~Candle();
	void Init(LPDIRECT3DDEVICE9 d3ddv, CSimon* simon, BulletManager* bulletManager, Explosion* explosion);
	void Update();
	void UpdateGunPoint();
	void Draw(int vpx, int vpy);
	void UpdateRect();
	void Destroy();
};

