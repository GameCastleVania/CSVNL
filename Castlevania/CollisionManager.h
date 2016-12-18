#pragma once
#include "recF.h"
#include "quadtree.h"

#include "simon.h"
#include "psound.h"
#include "map.h"
#include "EnemyManager.h"
#include "weaponManager.h"

class CollisionManager
{
private:
	CSimon* simon;
	Map* map;
	PSound* psound;
	EnemyManager* enemyManager;
	WeaponManager* weaponManager;
	Platform** platform;
public:
	CollisionManager(){}
	CollisionManager(CSimon* _Simon, EnemyManager* _EnemyManger, WeaponManager* _WeaponManager, Map* _Map, PSound* _Psound);
	~CollisionManager();

	void AddSpecialObjects(Platform** platform);
	Quadtree* CreateQuadTree(int vpx, int vpy);
	void ControlCollision(int vpx, int vpy);
	void CheckCollison(int vpx, int vpy);
};
