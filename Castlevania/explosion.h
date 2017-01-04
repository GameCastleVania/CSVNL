#pragma once
#include "sprite.h"
#include "gameobject.h"
#include <vector>

class Explode : public GameObject
{
private:
	Sprite* type1;
	Sprite* type2;
	Sprite* type3;
	Sprite* smallheart;
	Sprite* boomerangitem;
	Sprite* daggeritem;
	Sprite* axeitem;
	Sprite* firebombitem;
	Sprite* cash;
	Sprite* cross;
	Sprite* ball;
	Sprite* two;
	Sprite* three;
	Sprite* chickenleg;
	Sprite* bigheart;

	DWORD last_time;
	int index;
	int animation;
	bool visible = false;
public:
	Explode();
	~Explode();
	Explode(LPDIRECT3DDEVICE9 _d3ddv, int type, float x, float y);
	void Draw(int vpx, int vpy);
	void Update();
	void Set(int type, float x, float y, bool visible, int animation);
	bool Getvisible();
	int GetType();
	int GetAnimation();
	void UpdateRect();
};

typedef std::vector<Explode*> ListExplode;

class Explosion
{
private:
	DWORD last_time;
	DWORD life;
	ListExplode exlist;
public:
	Explosion();
	~Explosion();
	Explosion(LPDIRECT3DDEVICE9 _d3ddv);
	void Update();
	void Draw(int vpx, int vpy);
	void Get(int type, float x, float y, int animation);
	ListExplode GetList();
};