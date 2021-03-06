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
	STAND, //dung
	STANDW, //dung danh
	CROUCH, // ngoi
	CROUCHW, //ngoi danh
	RUN, // chay
	JUMP,// nhay
	JUMPW,
	LADDERUPLeftW, //len cau thang
	LADDERDOWNRightW, //xuong cau thang
	LADDERUPW, //len cau thang danh
	LADDERDOWNW, //xuong cau thang danh
	STANDUR,
	STANDDL,
	STANDUL,
	STANDDR,
	RUNUPR,
	RUNUPL,
	RUNDOWNL,
	RUNDOWNR,
	FLYL,
	FLYR
};

enum BulletType
{
	Fire_ball,
	Medusa_Snake,
	Bone_Bullet
};

enum WeaponType
{
	AXE,
	BOOMERANG,
	DAGGER,
	FIREBOMB,
	MORNINGSTAR,
};

enum EnemyState
{
	JUMPP,
	BEFOREDEAD,
	DEAD,
	EXPLODEE,
	SHOOTINGG,
	RUNN,
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
	LEFTDOWNS,
};

enum ItemType
{
	SMALLHEART,
	BIGHEART,
	AXEITEM,
	BOOMERANGITEM,
	DAGGERITEM,
	FIREBOMBITEM,
	CASH,
	CROSS,
	TIME,
	CHICKENLEG,
	TWO,
	THREE,
	BALL,
};

#endif