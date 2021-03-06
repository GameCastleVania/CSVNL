#include "CollisionManager.h"
#include <iostream>
#include <sstream>
#define ANIMATE_RATE 2
#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}

#define TILE_SIZE 32

extern int Current_State;
extern int SimonHP;
extern bool vpMove;
extern int count2w;
extern int stopUpdate;
extern int _time;

CollisionManager::CollisionManager(CSimon* _Simon, EnemyManager* _EnemyManger ,BulletManager* _BulletManager , WeaponManager* _WeaponManager, MorningStar* _MorningStar, Map* _Map, PSound* _Psound)
{
	simon = _Simon;
	map = _Map;
	psound = _Psound;
	enemyManager = _EnemyManger;
	weaponManager = _WeaponManager;
	morningStar = _MorningStar;
	bulletManager = _BulletManager;
	platform = NULL;
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
	RecF PrimaryWpRec = morningStar->CRec;
	RecFList mlist = map->CRecList();
	RecFList Ladderlist = map->CRecLadderList();
	RecFList Doorlist = map->CRecDoorList();
	BulletList blist = bulletManager->GetList();
	EnemyList elist = enemyManager->GetList();
	WeaponList simonWlist = weaponManager->GetSimonWList();
#pragma region Player collision
#pragma region Player collision with map
	//Player collide with map---------------------------------------------------------------------------

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
				simon->isOnGround = true;
				if ((simon->GetVY() < 0 && simon->GetY() - b->CRec.height - 28 > b->CRec.y) && simon->GetX() + 10 >= b->CRec.x && simon->GetX() - 10 <= b->CRec.x + b->CRec.width)
				{
					simon->isOnLadder = false;
					simon->_isOnLadder = false;
					simon->isJumpLeft = false;
					simon->isJumpRight = false;
					simon->SetY(b->CRec.y + 61);
					simon->SetVY(0);
					if ((simon->GetState() == JUMP || simon->GetState() == JUMPW || simon->GetState() == FLYL || simon->GetState() == FLYR || (simon->GetState() == STANDW && simon->isJumpLeft == true) || (simon->GetState() == STANDW && simon->isJumpRight == true)) && SimonHP > 0) simon->SetState(STAND);

				}

				//xet va cham theo truc x----------------------------------
				//simon di qua phai
				if ((simon->GetVX() > 0 && simon->GetX() + 10 > b->CRec.x))
				{
					if (b->CRec.height <= 40 && (simon->GetX() < b->CRec.x) && (simon->GetY() - 28 <= b->CRec.y + b->CRec.height))
					{
						if (simon->GetState() != RUNDOWNR && simon->GetState() != RUNUPR)
						{
							simon->SetX(b->CRec.x - 10);
							simon->SetVX(0);
						}
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
					if (b->CRec.height <= 40 && (simon->GetX() > b->CRec.x + b->CRec.width) && (simon->GetY() - 28 <= b->CRec.y + b->CRec.height))
					{
						if (simon->GetState() != RUNDOWNL && simon->GetState() != RUNUPL)
						{
							simon->SetX(b->CRec.x + b->CRec.width + 10);
							simon->SetVX(0);
						}
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

#pragma region Player collision with door
	//Player collide with door -----------------------------------------------------------------------

	quadtree->Retrieve(return_object, simon);
	for (auto x = return_object->begin(); x != return_object->end(); x++)
	{
		GameObject* b = x._Ptr->_Myval;
		if (b->GetType() == 3)
		{
			if (RecF::Collide(simon->CRec, b->CRec))
			{
				if (Current_State <= 5)
				{
					if ((simon->GetVX() < 0 && simon->GetX() - 10 > b->CRec.x))
					{
						if ((simon->GetY() >= b->CRec.y && (simon->GetY() - 28 < b->CRec.y + b->CRec.height)))
						{
							simon->SetVX(0);
							simon->allowCtrl = false;
							vpMove = true;
							if (simon->GetX() >= 1575) simon->SetState(STAND);
						}
					}
				}
				else
				{
					if ((simon->GetVX() > 0 && simon->GetX() > b->CRec.x))
					{
						if ((simon->GetY() >= b->CRec.y && (simon->GetY() - 28 < b->CRec.y + b->CRec.height)))
						{
							simon->SetVX(0);
							simon->allowCtrl = false;
							vpMove = true;
							if (Current_State == 7 && simon->GetX() <= 1500) simon->SetState(STAND);
							if (Current_State == 8 && simon->GetX() <= 2008) simon->SetState(STAND);
						}
					}
				}
			}
		}
	}
#pragma endregion

#pragma region Player collision with Platform
	//Player collisde with platform--------------------------------------------------------------------
	if (platform != NULL)
	{


		switch (Current_State)
		{
		case 3:
		{
			RecF temp = platform[0]->CRec;
			if (RecF::Collide(simon->CRec, temp))
			{
				if (simon->GetVY() < 0 && simon->GetY() - 28 > temp.y && simon->GetX() + 10 >= temp.x && simon->GetX() - 10 <= temp.x + temp.width)
				{
					simon->isJumpLeft = false;
					simon->isJumpRight = false;
					simon->SetY(temp.y + 29);
					simon->SetVY(0);
					if (simon->GetState() == JUMP || simon->GetState() == JUMPW) simon->SetState(STAND);
					if (platform[0]->IsMoved()) simon->SetX(simon->GetX() + platform[0]->GetVX());
				}
			}
		}
		break;
		case 4:
			for (int i = 0; i < 2; i++)
			{
				RecF _temp = platform[i]->CRec;
				if (RecF::Collide(simon->CRec, _temp))
				{
					if (simon->GetVY() < 0 && simon->GetY() - 28 > _temp.y && simon->GetX() + 10 >= _temp.x && simon->GetX() - 10 <= _temp.x + _temp.width)
					{
						simon->isJumpLeft = false;
						simon->isJumpRight = false;
						simon->SetY(_temp.y + 29);
						simon->SetVY(0);
						if (simon->GetState() == JUMP || simon->GetState() == JUMPW) simon->SetState(STAND);
						if (platform[i]->IsMoved()) simon->SetX(simon->GetX() + platform[i]->GetVX());
					}
				}
			}
			break;
		default:
			break;
		}
	}
#pragma endregion

#pragma region Player collision with ladderURDL
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

				if (b->CRec.type == 0 || b->CRec.type == 4)
				{
					///////////UPRIGHT && DOWNLEFT

					if (simon->isUpPress == true && simon->isRightPress == true && simon->isDownPress == false && simon->GetLRight() == true
						&& simon->GetY() - 20 > b->CRec.y && simon->GetX() - 2 >= b->CRec.x && simon->GetX() + 25 <= b->CRec.x + b->CRec.width)
					{
						simon->isOnGround = false;
						simon->isOnLadder = true;
						simon->_isOnLadder = false;
					}
				}


				///////// xet va cham dau tren of cau thang
				if (b->CRec.type == 2)
				{

					if (simon->isDownPress == true && simon->isLeftPress == true)
					{
						if (simon->isUpPress == false && simon->GetLRight() == false
							&& simon->GetY() - 28 - 32 > b->CRec.y && simon->GetX() <= b->CRec.x + b->CRec.width)
						{
							simon->isOnLadder = true;
							simon->_isOnLadder = false;
						}
					}
					else if (simon->GetY() - 28 - 32 >= b->CRec.y && simon->_isOnLadder == false)
					{
						simon->isOnLadder = false;
						simon->isJumpLeft = false;
						simon->isJumpRight = false;
						if (Current_State <= 5)
						simon->SetY(b->CRec.y + 61);
						else simon->SetY(b->CRec.y + 62);
						simon->SetVY(0);
						if (simon->GetState() == JUMP || simon->GetState() == JUMPW) simon->SetState(STAND);
					}
				}
			}
		}
	}
#pragma endregion

#pragma region Player collision with ladderULDR
	//Player collide with Ladder---------------------------------------------------------------------------

	//LADDER UPLEFT---------------------------------------------------------	
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

				if (b->CRec.type == 1 || b->CRec.type == 4)
				{
					///////////UPLEFT && DOWNRIGHT

					if (simon->isUpPress == true && simon->isLeftPress == true && simon->isDownPress == false && simon->GetLRight() == false
						&& simon->GetY() - 20 > b->CRec.y && simon->GetX() + 15 >= b->CRec.x + b->CRec.width)
					{
						simon->isOnGround = false;
						simon->_isOnLadder = true;
						simon->isOnLadder = false;
					}
				}


				///////// xet va cham dau tren of cau thang
				if (b->CRec.type == 3)
				{

					if (simon->isDownPress == true && simon->isRightPress == true)
					{
						if (simon->isUpPress == false && simon->GetLRight() == true
							&& simon->GetY() - 28 - 32 > b->CRec.y && simon->GetX() >= b->CRec.x)
						{
							simon->_isOnLadder = true;
							simon->isOnLadder = false;
						}
					}
					else if (simon->GetY() - 28 - 32 >= b->CRec.y && simon->isOnLadder == false)
					{
						simon->_isOnLadder = false;
						simon->isJumpLeft = false;
						simon->isJumpRight = false;
						simon->SetY(b->CRec.y + 62);
						simon->SetVY(0);
						if (simon->GetState() == JUMP || simon->GetState() == JUMPW) simon->SetState(STAND);
					}
				}
			}
		}
	}
#pragma endregion

#pragma region Player wp collision with Enemy
	//player weapon collide with enemy------------------------------------------------------------------
		for (int i = 0; i < elist.size(); i++)
		{
			return_object->clear();
			quadtree->Retrieve(return_object, elist[i]);
			for (auto x = return_object->begin(); x != return_object->end(); x++)
			{
				GameObject* b = x._Ptr->_Myval;
				//DBOUT(b->GetType() << endl);
				if (b->GetType() == 6 && elist[i]->GetType() != 8)
				{
					if (RecF::Collide(elist[i]->CRec, b->CRec))
						{
							if (elist[i]->_stopUpdate == false)
							{
								elist[i]->_stopUpdate = true;
								elist[i]->LowerHP();
							}
						}	
					else elist[i]->_stopUpdate = false;
				}
			}		
		}
		

		for (int i = 0; i < elist.size(); i++)
		{
			return_object->clear();
			quadtree->Retrieve(return_object, elist[i]);
			if (RecF::Collide(elist[i]->CRec, morningStar->CRec) && elist[i]->GetType() != 8 && morningStar->fight == true)
			{
				if (elist[i]->stopUpdate == false)
				{
					elist[i]->stopUpdate = true;
					elist[i]->LowerHP();
				}
			}
			else elist[i]->stopUpdate = false;
		}


#pragma endregion


#pragma region Player collision with Enemy
	//player collide with enemy------------------------------------------------------------------
	
	quadtree->Retrieve(return_object, simon);
	for (auto x = return_object->begin(); x != return_object->end(); x++)
	{
		GameObject* b = x._Ptr->_Myval;
		if ((b->GetType() == 4 || b->GetType() == 5 || b->GetType() == 8) && SimonHP >= 0 && b->GetType() != 9)
		{	
			if (RecF::Collide(b->CRec, simon->CRec))
			{		
					simon->LowerHP();
					simon->Kill();
			}
		}
	}
	


#pragma endregion

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
	RecFList Ladderlist = map->CRecLadderList();
	RecFList Doorlist = map->CRecDoorList();
	EnemyList elist = enemyManager->GetList(); 
	BulletList blist = bulletManager->GetList();
	WeaponList simonWlist = weaponManager->GetSimonWList();

	for (int i = 0; i < mlist.size(); i++){
		quadtree->Insert(&mlist[i]);
	}

	for (int i = 0; i < Ladderlist.size(); i++){
		quadtree->InsertLadder(&Ladderlist[i]);
	}

	for (int i = 0; i < Doorlist.size(); i++){
		quadtree->InsertDoor(&Doorlist[i]);
	}

	for (int i = 0; i < elist.size(); i++){
		quadtree->Insert(elist[i]);
	}

	for (int i = 0; i < simonWlist.size(); i++){
		if (simonWlist[i]->GetVisible()) quadtree->Insert(simonWlist[i]);
	}

	for (int i = 0; i < blist.size(); i++){
		if (blist[i]->GetVisible()) quadtree->Insert(blist[i]);
	}

	return quadtree;
}

//Summary all collision activity
void CollisionManager::ControlCollision(int vpx, int vpy)
{
	CheckCollison(vpx, vpy);
}

void CollisionManager::AddSpecialObjects(Platform** _platform)
{
	platform = _platform;
}