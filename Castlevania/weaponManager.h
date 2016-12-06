#pragma once
#include "Axe.h"
#include "Boomerang.h"
#include "Dagger.h"
#include "FireBomb.h"
#include "MorningStar.h"
#include "weapon.h"
#include "keyboard.h"
#include "psound.h"
#include "simon.h"
#include "utils.h"
#include <vector>

typedef std::vector <Weapon*> WeaponList;
class WeaponManager
{
protected:
	Keyboard* kbd;
	PSound* psound;
	CSimon* simon;
	WeaponList bList;
	WeaponList playerBList;
	Direction direc;

	//Player bullet count
	int timeFire; //fire time between each bullet
	int fireRate; //bullet fire rate
	int bulletCount; //player bullet count
	int timeLimit; //time limit between 3 bullet 
	int nextbullet;

	//Weapon type temp
	Weapon weapon;
	Axe axe;
	Boomerang bmerang;
	Dagger dagger;
	FireBomb fbomb;
	MorningStar mnstar;

public:
	WeaponManager(){}
	WeaponManager(LPDIRECT3DDEVICE9 _d3ddv, Keyboard* _keyboard, CSimon* _simon, Explosion* _explosion, PSound* _psound);
	~WeaponManager();

	void Draw(int vpx, int vpy);
	void Update(int vpx, int vpy);
	void Get(BulletType type, float x, float y, float vx, float vy, bool isPlayer);
	void Get(int boss, float x, float y, float vx, float vy);
	void LowerTimeLimit();

	void PlayerShoot();
	//void SetPLayerBType(BonusType t);

	WeaponList GetList();
	WeaponList GetpList();

};

struct Point
{
	float x;
	float y;
};

