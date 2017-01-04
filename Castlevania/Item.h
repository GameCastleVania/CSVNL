#pragma once
#include "gameobject.h"
#include "sprite.h"
#include <vector>

class Item :
	public GameObject
{
protected:
	int typerandom;
	bool visible = false; // = true thi draw item
	int timeitem = 0; //thoi gian item bien mat

	Sprite* smallheart;
	Sprite* boomerangitem;
	Sprite* daggeritem;
	Sprite* firebombitem;
	Sprite* cash;
	Sprite* cross;
	Sprite* ball;
	Sprite* two;
	Sprite* three;
	//Sprite* timeitem;
	Sprite* chickenleg;
	Sprite* bigheart;
public:
	Item();
	Item(LPDIRECT3DDEVICE9 d3ddv, float x, float y, int a);
	~Item();

	void Draw(int vpx, int vpy);
	void Update();
	void Set(float x, float y, bool visible, int a);

	bool GetVisible();
};

typedef std::vector<Item*> ItemList;

class ItemManager
{
protected:
	ItemList item;

public:
	ItemManager();
	ItemManager(LPDIRECT3DDEVICE9 _d3ddv);
	~ItemManager();

	void Draw(int vpx, int vpy);
	void Update();
	void Get(float X, float Y, int a);

	ItemList GetList();
};
