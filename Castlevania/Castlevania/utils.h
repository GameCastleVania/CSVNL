#ifndef __UTILS_H_
#define __UTILS_H_

#include <d3d9.h>
//Map
#define TILE_SIZE 32

//Bullet
#define BULLET_SPEED 8
#define BULLET_NORMAL_RATE 10

LPDIRECT3DSURFACE9 CreateSurfaceFromFile(LPDIRECT3DDEVICE9 d3ddv, char *FilePath);

enum PlayerState
{
	STAND,
	STANDS,
	CROUCH,
	RUN,
	RUNS,
	RUNUP,
	RUNDOWN,
	JUMP,
	JUMPDOWN,
	SWIM,
	SWIMS,
	SWIMUP,
	SWIMUPS,
	DIVE,
	FALL,
	LOOKUP
};

enum BulletType
{
	Fire_ball,
	Medusa_Snake,
};

enum EnemyState
{
	JUMPP,
	BEFOREDEAD,
	DEAD,
	EXPLODEE,
	SHOOTINGG,
	RUNN
};

enum Direction
{
	LEFT,
	LEFTUPS,
	LEFTUP,
	UP,
	RIGHTUP,
	RIGHTUPS,
	RIGHT,
	RIGHTDOWN,
	RIGHTDOWNS,
	DOWN,
	LEFTDOWN,
	LEFTDOWNS
};
#endif