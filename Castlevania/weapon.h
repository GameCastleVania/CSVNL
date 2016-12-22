#pragma once
#include <d3dx9.h>
#include "gameobject.h"
#include "sprite.h"
#include "simon.h"
#include "explosion.h"

class Weapon : public GameObject
{
protected:
	bool ex = false;
	bool visible;
	Explosion* explosion;
	CSimon* simon;
	bool falling = false; // trang thai len cao roi xuong cua Axe va FireBomb
public:
	Weapon();
	~Weapon();
	virtual void Draw(float vpx, float vpy);
	virtual void Update();
	virtual void Destroy();

#pragma region Get_Set
	void Set(float X, float Y, float VX, float VY);
	void Set(float, float, float, float, int);
	void SetByPlayer(bool set);
	bool CanExplode();
	bool SetFalling(bool val);
	bool GetFalling();
	void SetVisible(bool vis);
	bool GetVisible();

#pragma endregion
};

