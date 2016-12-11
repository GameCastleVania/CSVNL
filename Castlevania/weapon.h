#pragma once
#include <d3dx9.h>
#include "gameobject.h"
#include "sprite.h"
#include "simon.h"
#include "explosion.h"

class Weapon : public GameObject
{
protected:
	bool ex;
	Explosion* explosion;
	CSimon* simon;
	bool fight;
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
	bool SetFight(bool val);
	bool GetFight();

#pragma endregion
};

