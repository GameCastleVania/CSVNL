#pragma once
#include "Enemy.h"
#include "TMXParser.h"
#include "BulletManager.h"

class EnemyManager
{
private:
	EnemyList enemyList;
public:
	EnemyManager();
	EnemyManager(LPDIRECT3DDEVICE9 _d3ddv, char* _filename, CSimon* simon, BulletManager* _bulletManager, Explosion* _explosion);
	~EnemyManager();

	void Update();
	void Draw(int vpx, int vpy);
	EnemyList GetList();
};

