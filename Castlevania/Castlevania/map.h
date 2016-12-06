#ifndef _MAP_H_
#define _MAP_H_
#pragma once
#include<stdio.h>
#include"sprite.h"
#include"recF.h"
#include"TMXParser.h"
#include "utils.h"
#include "quadtree.h"

class Map{
private:
	Sprite* _spriteSheet;
	RecFList _collisionRecs;

	int _width;
	int _height;
	int* _mapArr;
	int animation;
public:
	Map();
	Map(LPDIRECT3DDEVICE9 _d3ddv, char *spriteSheet, char* fileName);
	~Map();
	void Update();
	void Draw(int vpx, int vpy);

	RecFList CRecList();

	int Width();
	int Height();
	void SetMap(int width, int height, int* mapArr, RecFList collisionRecs);
};
#endif