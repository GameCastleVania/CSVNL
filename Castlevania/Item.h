#pragma once
#include "gameobject.h"
#include "sprite.h"
#include <vector>

class Item :
	public GameObject
{
protected:
	ItemType itype;
	bool visible = false; // = true thi draw item
	int time = 0; //thoi gian item bien mat

public:
	Item();
	Item(LPDIRECT3DDEVICE9 d3ddv);
	~Item();

	void Draw(int vpx, int vpy);
	void Update();
	void Destroy();

	ItemType GetType();

	void Set(float, float, float, float);
	void Set(float, float);
	void Set(float, float, float, float, ItemType);

	bool GetVisible()
	{
		return visible;
	}

	bool SetVisible(bool value)
	{
		return visible = value;
	}
};
typedef std::vector<Item*> ItemList;
