#include "CollisionManager.h"

#define TILE_SIZE 32


CollisionManager::CollisionManager(CSimon* _Simon, Map* _Map, PSound* _Psound)
{
	simon = _Simon;
	map = _Map;
	psound = _Psound;

}

CollisionManager::~CollisionManager()
{}

//Check collision and reaction
void CollisionManager::CheckCollison(int vpx, int vpy)
{
	Quadtree* quadtree = CreateQuadTree(vpx, vpy);
	ObjectList* return_object = new ObjectList();
	//All game list
	RecF simonRec = simon->CRec;
	RecFList mlist = map->CRecList();

#pragma region Player collision
	//Bullet, enemy, bonus collide with player------------------------------------------------------------

	//Grenage explosion with player

	//Player collide with bridge-----------------------------------------------------------------------

	//Player collisde with platform--------------------------------------------------------------------

	//Player collide with map---------------------------------------------------------------------------
	return_object->clear();
	quadtree->Retrieve(return_object, simon);
	for (auto x = return_object->begin(); x != return_object->end(); x++)
	{
		GameObject* b = x._Ptr->_Myval;
		if (b->GetType() == 1)
		{
			if (int a = RecF::Collide(simon->CRec, b->CRec))
			{
				if ((simon->GetVY() < 0 && simon->GetY() - 10 > b->CRec.y))
				{
					simon->SetY(b->CRec.y + 31);
					simon->SetVY(0);
					if (simon->GetState() == JUMP) simon->SetState(STAND);
				}
			}
		}
	}
#pragma endregion

	quadtree->Clear();
	delete return_object;
	delete quadtree;
}

Quadtree* CollisionManager::CreateQuadTree(int vpx, int vpy)
{
	//Init base game region for detecting collision
	Quadtree* quadtree = new Quadtree(1, new RecF(vpx, vpy - 480, 512, 480));

	RecFList mlist = map->CRecList();

	for (int i = 0; i < mlist.size(); i++){
		quadtree->Insert(&mlist[i]);
	}
	return quadtree;
}

//Summary all collision activity
void CollisionManager::ControlCollision(int vpx, int vpy)
{
	CheckCollison(vpx, vpy);
}