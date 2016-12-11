#include "Quadtree.h"


Quadtree::Quadtree()
{}

Quadtree::Quadtree(int pLevel, RecF* region)
{
	level = pLevel;
	this->region = region;
	objList = new ObjectList();
	nodes = NULL;
}


Quadtree::~Quadtree()
{}

void Quadtree::Clear()
{
	//Clear all nodes
	if (nodes)
	{
		for (int i = 0; i < 4; i++)
		{
			nodes[i]->Clear();
			delete nodes[i];
		}
		delete[] nodes;
	}

	//Clear current quadtree
	objList->clear();

	delete objList;
	delete region;
}

bool Quadtree::IsContain(GameObject* object)
{
	RecF bound = object->CRec;

	return !(bound.x + bound.width < region->x ||
		bound.y + bound.height < region->y ||
		bound.x > region->x + region->width ||
		bound.y> region->y + region->height);
}

void Quadtree::Split()
{
	int subWidth = (int)(region->width / 2);
	int subHeight = (int)(region->height / 2);
	int x = (int)region->x;
	int y = (int)region->y;

	nodes = new Quadtree*[4];
	nodes[0] = new Quadtree(level + 1, new RecF(x, y, subWidth, subHeight));
	nodes[1] = new Quadtree(level + 1, new RecF(x + subWidth, y, subWidth, subHeight));
	nodes[2] = new Quadtree(level + 1, new RecF(x, y + subHeight, subWidth, subHeight));
	nodes[3] = new Quadtree(level + 1, new RecF(x + subWidth, y + subHeight, subWidth, subHeight));
}

void Quadtree::Insert(GameObject* obj)
{
	//Insert entity into corresponding nodes
	if (nodes)
	{
		if (nodes[0]->IsContain(obj))
			nodes[0]->Insert(obj);
		if (nodes[1]->IsContain(obj))
			nodes[1]->Insert(obj);
		if (nodes[2]->IsContain(obj))
			nodes[2]->Insert(obj);
		if (nodes[3]->IsContain(obj))
			nodes[3]->Insert(obj);
	}

	//Insert entity into current quadtree
	if (this->IsContain(obj))
		objList->push_back(obj);

	//Split and move all objects in list into it’s corresponding nodes
	if (objList->size() > MAX_OBJECT && level < MAX_LEVEL)
	{
		Split();

		while (!objList->empty())
		{
			if (nodes[0]->IsContain(objList->back()))
				nodes[0]->Insert(objList->back());
			if (nodes[1]->IsContain(objList->back()))
				nodes[1]->Insert(objList->back());
			if (nodes[2]->IsContain(objList->back()))
				nodes[2]->Insert(objList->back());
			if (nodes[3]->IsContain(objList->back()))
				nodes[3]->Insert(objList->back());

			objList->pop_back();
		}
	}
}

void Quadtree::Insert(RecF* rec)
{
	GameObject* g = new GameObject();
	g->CRec = *rec;
	g->SetType(1);
	Insert(g);
}

void Quadtree::InsertLadder(RecF* rec)
{
	GameObject* g = new GameObject();
	g->CRec = *rec;
	g->SetType(2);
	Insert(g);
}

ObjectList* Quadtree::Retrieve(ObjectList* returnObjects, GameObject* object)
{
	if (nodes != NULL)
	{
		if (nodes[0]->IsContain(object))
			nodes[0]->Retrieve(returnObjects, object);
		if (nodes[1]->IsContain(object))
			nodes[1]->Retrieve(returnObjects, object);
		if (nodes[2]->IsContain(object))
			nodes[2]->Retrieve(returnObjects, object);
		if (nodes[3]->IsContain(object))
			nodes[3]->Retrieve(returnObjects, object);
	}
	//Add all entities in current region into returnObjects
	if (this->IsContain(object))
	{
		for (auto i = objList->begin(); i != objList->end(); i++)
		{
			//if (object != i._Ptr->_Myval)
			returnObjects->push_back(i._Ptr->_Myval);
		}
	}
	return returnObjects;
}

//ObjectList* Quadtree::Retrieve(ObjectList* returnObject, RecF* CollisionRec)
//{
//	GameObject* g = new GameObject();
//	g->CRec = *CollisionRec;
//	return Retrieve(returnObject, g);
//}