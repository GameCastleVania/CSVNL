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
	WeaponList simonWList;
	Direction direc;

	bool upfight; // xet trang thai tha phim enter
	bool up2nd; // xet trang thai tha phim F
	bool fight; // xet trang thai phim enter co nhan hay khong
	//int count; // xet so lan vu khi thu 2 dc nem 
	int time = 0;

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

	void Get(WeaponType type, float x, float y, float vx, float vy);
	void PlayerShoot();
	//void SetPLayerBType(BonusType t);



	WeaponList GetSimonWList();

};