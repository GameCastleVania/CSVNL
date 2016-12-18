#pragma once
#include <d3dx9.h>
#include <vector>
#include "keyboard.h"
#include "sprite.h"
#include "gameobject.h"
#include "simon.h"
#include "utils.h"
#include "explosion.h"
#include "BulletManager.h"
#include "ItemManager.h"

extern int Score;

class Enemy : public GameObject
{
protected:

	Direction direction;
	CSimon* simon;
	BulletManager* bulletManager;
	Explosion* explosion;

	float gunx, guny;
	bool shooting; // ban
	float PosX, PosY;
	int HP;
	bool LRight;
	int isDead; // 0 la song, 1 truoc khi chet, 2 chet
	bool wasHit;
	int state;
	bool visible;
	bool exploded;
	bool ready;
	int hitTime;
public:
	Enemy()
	{
		HP = 0;
		visible = true;
		ready = false;
		type = 4;
		state = 0;
	}
	Enemy(float X, float Y)
	{
		x = X;
		y = Y;
	}
	~Enemy()
	{}

	virtual void Init(LPDIRECT3DDEVICE9 d3ddv, CSimon* simon, BulletManager* bulletManager, Explosion* explosion) = 0;
	virtual void Update() = 0;
	virtual void UpdateGunPoint() = 0;
	virtual void Draw(int vpx, int vpy) = 0;
	virtual void Destroy() = 0;


#pragma region Get_Set

	int GetHP()
	{
		return HP;
	}
	float GetGunX()
	{
		return gunx;
	}
	float GetGunY()
	{
		return guny;
	}
	bool GetShoot()
	{
		return shooting;
	}
	Direction GetDirection()
	{
		return direction;
	}
	void SetHP(int hp)
	{
		HP = hp;
	}
	void LowerHP()
	{
		HP--;
	}
	bool IsDead()
	{
		if (isDead == 2) return true;
	}
	bool GetVisible()
	{
		return visible;
	}
	void SetState(int s)
	{
		state = s;
	}
	int GetState()
	{
		return state;
	}
	void SetHit(bool hit)
	{
		wasHit = hit;
	}
};
#pragma endregion

typedef std::vector<Enemy*> EnemyList;