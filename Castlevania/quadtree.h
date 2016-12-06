#pragma once
#include "gameobject.h"
#include <list>
#include "recF.h"
#include <Windows.h>
using namespace std;
#define MAX_OBJECT 17
#define MAX_LEVEL 15

// 0  |  1
// -------
// 2  |  3
typedef list<GameObject*> ObjectList;


class Quadtree
{
private:
	int level, nodeID;
	char *id;
	ObjectList* objList;
	RecF* region;
	Quadtree** nodes;

	bool IsContain(GameObject* object);
	void Split();
public:
	Quadtree();
	Quadtree(int pLevel, RecF* region);
	Quadtree(int _nodeID, float _x, float _y, float _width, float _height, char *_id);
	~Quadtree();

	void Clear();
	void Insert(GameObject* obj);
	void Insert(RecF* rec);
	ObjectList* Retrieve(ObjectList* returnObject, GameObject* object);
	//ObjectList* Retrieve(ObjectList* returnObject, RecF* CollisionRec);
};

