#pragma once
#include "recF.h"
#include "quadtree.h"

#include "simon.h"
#include "psound.h"
#include "map.h"


class CollisionManager
{
private:
	CSimon* simon;
	Map* map;
	PSound* psound;
public:
	CollisionManager(){}
	CollisionManager(CSimon* _Simon, Map* _Map, PSound* _Psound);
	~CollisionManager();

	Quadtree* CreateQuadTree(int vpx, int vpy);
	void ControlCollision(int vpx, int vpy);
	void CheckCollison(int vpx, int vpy);
};
