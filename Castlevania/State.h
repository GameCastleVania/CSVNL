#pragma once
#include<d3dx9.h>
#include "sound.h"
#include "psound.h"
#include "keyboard.h"
#include "map.h"
#include "simon.h"
#include "CollisionManager.h"
#include "BulletManager.h"
#include "weaponManager.h"
#include "EnemyManager.h"
#include "explosion.h"
#include "MorningStar.h"

class State
{
protected:
	LPDIRECT3DDEVICE9 d3ddv;
	Keyboard* kbd;

	PSound* psound;
	Map* map;
	CSimon* simon;
	MorningStar* mstar;
	BulletManager* bulletManager;
	WeaponManager* weaponManager;
	EnemyManager* enemyManager;
	Explosion* explosion;
	CollisionManager* collisionManager;

public:
	State(){}
	~State(){}
	virtual void Init(LPDIRECT3DDEVICE9 d3ddv, DSound* Audio, Keyboard* kbd) = 0;
	virtual void Update(int &vpx, int &vpy) = 0;
	virtual void Draw(int vpx, int vpy) = 0;
	virtual void Exit(int &vpx, int &vpy) = 0;

};

