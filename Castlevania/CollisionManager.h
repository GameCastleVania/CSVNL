#pragma once
#include "recF.h"
#include "quadtree.h"

#include "simon.h"
#include "psound.h"
#include "map.h"
#include "EnemyManager.h"
#include "weaponManager.h"
#include "MorningStar.h"

class CollisionManager
{
private:
	CSimon* simon;
	Map* map;
	PSound* psound;
	EnemyManager* enemyManager;
	WeaponManager* weaponManager;
	MorningStar* morningStar;
	Platform** platform;
	BulletManager* bulletManager;
	int dem = 0;
	int time = 0;
public:
	CollisionManager(){}
	CollisionManager(CSimon* _Simon, EnemyManager* _EnemyManger, BulletManager* _BulletManager, WeaponManager* _WeaponManager, MorningStar* _MorningStar, Map* _Map, PSound* _Psound);
	~CollisionManager();

	void AddSpecialObjects(Platform** platform);
	Quadtree* CreateQuadTree(int vpx, int vpy);
	void ControlCollision(int vpx, int vpy);
	void CheckCollison(int vpx, int vpy);
};
