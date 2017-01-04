#pragma once
#include "FireBall.h"
#include "Boss2Bullet.h"
#include "SkeletonBullet.h"
#include "Boss3Bullet.h"
#include "Bullet.h"
#include "keyboard.h"
#include "psound.h"
#include "utils.h"
#include <vector>

typedef vector<Bullet*> BulletList;
class BulletManager
{
protected:
	Keyboard* kbd;
	PSound* psound;
	BulletList bList;
	BulletList bossBList;
	Direction direc;

	//Player bullet count
	int timeFire; //fire time between each bullet
	int fireRate; //bullet fire rate
	int timeLimit; //time limit between 3 bullet 
	int nextbullet;

	//Bullet type temp
	Bullet bullet;
	FireBall fireball;
	SkeletonBullet boneBullet;
	Boss2Bullet boss2Bullet;
	Boss3Bullet boss3Bullet;
public:
	BulletManager() {}
	BulletManager(LPDIRECT3DDEVICE9 _d3ddv, Keyboard* _keyboard, Explosion* _explosion, PSound* _psound);
	~BulletManager();

	void Draw(int vpx, int vpy);
	void Update(int vpx, int vpy);
	void Get(BulletType type, float x, float y, float vx, float vy, bool isPlayer);
	void Get(int boss, float x, float y, float vx, float vy);
	void LowerTimeLimit();

	BulletList GetList();
	BulletList GetBossList();
};

struct Point
{
	float x;
	float y;
};

