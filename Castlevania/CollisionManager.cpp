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
	Keyboard* kbd;
	//All game list
	RecF simonRec = simon->CRec;
	RecFList mlist = map->CRecList();
	RecFList Ladderlist = map->CRecLadderList();

#pragma region Player collision with map
	//Bullet, enemy, bonus collide with player------------------------------------------------------------

	//Grenage explosion with player

	//Player collide with bridge-----------------------------------------------------------------------

	//Player collisde with platform--------------------------------------------------------------------

	//Player collide with map---------------------------------------------------------------------------
	bool isOnLadder;

	return_object->clear();
	quadtree->Retrieve(return_object, simon);
	for (auto x = return_object->begin(); x != return_object->end(); x++)
	{
		GameObject* b = x._Ptr->_Myval;
		if (b->GetType() == 1)
		{
			if (RecF::Collide(simon->CRec, b->CRec))
			{
				//xet va cham theo truc y----------------------------------
				if ((simon->GetVY() < 0 && simon->GetY() - b->CRec.height - 28 > b->CRec.y) && simon->GetX() + 10 >= b->CRec.x && simon->GetX() - 10 <= b->CRec.x + b->CRec.width)
				{
					isOnLadder = false;
					simon->isOnLadder = false;
					simon->SetY(b->CRec.y + 60);
					simon->SetVY(0);
					if (simon->GetState() == JUMP || simon->GetState() == JUMPFIGHT) simon->SetState(STAND);
					
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
			}
		}
	}
#pragma endregion

#pragma region Player collision with ladderUR
	//Player collide with Ladder---------------------------------------------------------------------------

	//LADDER UPRIGHT---------------------------------------------------------	
	return_object->clear();
	quadtree->Retrieve(return_object, simon);
	for (auto x = return_object->begin(); x != return_object->end(); x++)
	{
		GameObject* b = x._Ptr->_Myval;
		if (b->GetType() == 2)
		{
			if (RecF::Collide(simon->CRec, b->CRec))
			{
				/////va cham cau thang

				if (b->CRec.type == 0 || b->CRec.type == 4 || b->CRec.type == 2)
				{
					///////////UPRIGHT

					if (simon->isUpPress == true && simon->isRightPress == true && simon->isDownPress == false && simon->GetLRight() == true
						&& simon->GetY() - 20 > b->CRec.y && simon->GetX() - 7 >= b->CRec.x && simon->GetX() + 20 <= b->CRec.x + b->CRec.width)
					{
						isOnLadder = true;
						simon->isOnLadder = true;
						simon->ladderUPRight();
					}

					if ((simon->isRightPress == false || simon->isUpPress == false) && simon->isDownPress == false && simon->isOnLadder == true && simon->GetLRight() == true
						&& simon->GetY() - 20 - 32 > b->CRec.y)
					{
						simon->SetState(STANDUR);
						isOnLadder = true;
						simon->isOnLadder = true;
						simon->SetY(b->CRec.y + 60);
						simon->SetVY(0);
					}
				}


				///////// xet va cham dau tren of cau thang
				if (b->CRec.type == 2)
				{
					if (simon->GetY() - 28 - 32 >= b->CRec.y)
					{
						isOnLadder = false;
						simon->isOnLadder = false;
					}
				}
			}
		}
	}
#pragma endregion

	//#pragma region Player collision with ladderDL
	////LADDER DOWNLEFT---------------------------------------------------------	
	//	return_object->clear();
	//	quadtree->Retrieve(return_object, simon);
	//	for (auto x = return_object->begin(); x != return_object->end(); x++)
	//	{
	//		GameObject* b = x._Ptr->_Myval;
	//		if (b->GetType() == 2)
	//		{
	//			if (RecF::Collide(simon->CRec, b->CRec))
	//			{
	//				
	//				///////// xet va cham dau tren of cau thang
	//				if (b->CRec.type == 2 || b->CRec.type == 4 )
	//				{
	//					if (simon->isDownPress == true && simon->isUpPress == false && simon->GetLRight() == false && simon->GetY() - 20 > b->CRec.y && simon->GetX() >= b->CRec.x && simon->GetX() + 13 <= b->CRec.x + b->CRec.width)
	//					{
	//						isOnLadder = true;
	//						simon->isOnLadder = true;
	//						simon->ladderDOWNLeft();
	//					}
	//
	//					if (simon->isDownPress == false && simon->isUpPress == false && simon->isOnLadder == true && simon->GetLRight() == false && simon->GetY() - 20 - 32 > b->CRec.y)
	//					{
	//						simon->SetState(STANDDL);
	//						isOnLadder = true;
	//						simon->isOnLadder = true;
	//						simon->SetY(b->CRec.y + 61);
	//						simon->SetVY(0);
	//					}
	//				}
	//
	//				/////va cham cau thang
	//
	//				if (b->CRec.type == 0)
	//				{
	//
	//					if (simon->GetY() - 28 - 32 >= b->CRec.y)
	//					{
	//						isOnLadder = false;
	//						simon->isOnLadder = false;
	//					}
	//
	//					if (simon->isDownPress == true && simon->isUpPress ==  false && simon->GetLRight() == false && simon->GetY() - 20 > b->CRec.y && simon->GetX() >= b->CRec.x && simon->GetX() + 13 <= b->CRec.x + b->CRec.width)
	//					{
	//						isOnLadder = true;
	//						simon->isOnLadder = true;
	//						simon->ladderDOWNLeft();
	//					}
	//
	//					if (simon->isUpPress == false && simon->isDownPress == false && simon->isOnLadder == true && simon->GetLRight() == true && simon->GetY() - 20 - 32 > b->CRec.y)
	//					{
	//						simon->SetState(STANDDL);
	//						isOnLadder = true;
	//						simon->isOnLadder = true;
	//						simon->SetY(b->CRec.y + 61);
	//						simon->SetVY(0);
	//					}
	//				}
	//
	//
	//
	//			}
	//		}
	//	}
	//#pragma endregion

	quadtree->Clear();
	delete return_object;
	delete quadtree;
}

Quadtree* CollisionManager::CreateQuadTree(int vpx, int vpy)
{
	//Init base game region for detecting collision
	Quadtree* quadtree = new Quadtree(1, new RecF(vpx, vpy - 480, 512, 480));

	RecFList mlist = map->CRecList();
	RecFList Ladderlist = map->CRecLadderList();

	for (int i = 0; i < mlist.size(); i++){
		quadtree->Insert(&mlist[i]);
	}

	for (int i = 0; i < Ladderlist.size(); i++){
		quadtree->InsertLadder(&Ladderlist[i]);
	}
	return quadtree;
}

//Summary all collision activity
void CollisionManager::ControlCollision(int vpx, int vpy)
{
	CheckCollison(vpx, vpy);
}