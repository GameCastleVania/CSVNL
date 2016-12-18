#include "EnemyManager.h"


EnemyManager::EnemyManager()
{}


EnemyManager::~EnemyManager()
{}

EnemyManager::EnemyManager(LPDIRECT3DDEVICE9 _d3ddv, char* _filename, CSimon* _simon, BulletManager* _bulletManager, Explosion* _explosion)
{
	enemyList = EnemyList();

	Parser tmx(_filename);
	tmx.ReadEnemy("SpearKnights", enemyList);
	tmx.ReadEnemy("Bats", enemyList);
	tmx.ReadEnemy("BoneTowers", enemyList);
	tmx.ReadEnemy("Ghosts", enemyList);
	tmx.ReadEnemy("MedusaHeads", enemyList);
	tmx.ReadEnemy("CandlesSmall", enemyList);
	tmx.ReadEnemy("Boss2", enemyList);
	tmx.ReadEnemy("DownUp", enemyList);
	//tmx.ReadEnemy("que", enemyList);

	for (int i = 0; i < enemyList.size(); i++)
	{
		enemyList[i]->Init(_d3ddv, _simon, _bulletManager, _explosion);
	}
}

void EnemyManager::Update()
{
	for (int i = 0; i < enemyList.size(); i++)
	{
		enemyList[i]->Update();
	}
}

void EnemyManager::Draw(int vpx, int vpy)
{
	for (int i = 0; i < enemyList.size(); i++)
	{
		enemyList[i]->Draw(vpx, vpy);
	}
}

void EnemyManager::Destroy()
{
	for (int i = 0; i < enemyList.size(); i++)
	{
		enemyList[i]->Destroy();
	}
}

EnemyList EnemyManager::GetList()
{
	return enemyList;
}