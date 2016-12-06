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
				//xet va cham theo truc y----------------------------------
				if ((simon->GetVY() < 0 && simon->GetY() - b->CRec.height - 28 > b->CRec.y))
				{
					simon->SetY(b->CRec.y + 60);
					simon->SetVY(0);
					if (simon->GetState() == JUMP) simon->SetState(STAND);
				}

				//xet va cham theo truc x----------------------------------
				//simon di qua phai
				if ((simon->GetVX() > 0 && simon->GetX() + 10 > b->CRec.x))
				{
					if (b->CRec.height <= 40 && (simon->GetX() < b->CRec.x) && (simon->GetY() <= b->CRec.y + b->CRec.height))
					{
						simon->SetX(b->CRec.x - 10);
						simon->SetVX(0);
					}
					else if (b->CRec.height > 40 && ((simon->GetY() >= b->CRec.y) && (simon->GetY() - 28 < b->CRec.y + b->CRec.height)))
					{
						simon->SetX(b->CRec.x - 10);
						simon->SetVX(0);
					}
				}
				//simon qua trai
				if ((simon->GetVX() < 0 && simon->GetX() - 10 > b->CRec.x))
				{
					if (b->CRec.height <= 40 && (simon->GetX() > b->CRec.x + b->CRec.width) && (simon->GetY() <= b->CRec.y + b->CRec.height))
					{
						simon->SetX(b->CRec.x + b->CRec.width + 10);
						simon->SetVX(0);
					}
					else if (b->CRec.height > 40 && (simon->GetY() >= b->CRec.y && (simon->GetY() - 28 < b->CRec.y + b->CRec.height)))
					{
						simon->SetX(b->CRec.x + b->CRec.width + 10);
						simon->SetVX(0);
					}
				}

				/*	else if ((simon->GetVX() < 0 && simon->GetX() - 10 < b->CRec.x) && (simon->GetY() >= b->CRec.y && simon->GetY() < b->CRec.y + b->CRec.height))
				{
				simon->SetX(b->CRec.x + 10);
				simon->SetVX(0);
				}*/

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