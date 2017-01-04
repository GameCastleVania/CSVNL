#ifndef _MAP_H_
#define _MAP_H_
#pragma once
#include<stdio.h>
#include"sprite.h"
#include"recF.h"
#include"TMXParser.h"
#include "utils.h"
#include "quadtree.h"
#include "font.h"
#include "HealthBar.h"
#include "keyboard.h"

class Map{
private:
	Sprite* _spriteSheet;
	RecFList _collisionRecs;
	RecFList _ladderRecs;
	RecFList _doorRecs;

	int _width;
	int _height;
	int* _mapArr;
	char* ktustage;

	//game board
	Font* text;
	Sprite* gameboard;
	HealthBar* healthbar;
	Keyboard* kbd;

public:
	Map();
	Map(LPDIRECT3DDEVICE9 _d3ddv, char *spriteSheet, char* fileName, Keyboard* kbd);
	~Map();
	void Update();
	void Draw(int vpx, int vpy);

	RecFList CRecList();
	RecFList CRecLadderList();
	RecFList CRecDoorList();

	int Width();
	int Height();
	void SetMap(int width, int height, int* mapArr, RecFList collisionRecs, RecFList _ladderRecs, RecFList _doorRecs);
};
#endif