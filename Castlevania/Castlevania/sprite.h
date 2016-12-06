#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>

class Sprite {
protected:
	LPDIRECT3DTEXTURE9 image;				// The container of all the sprites
	LPDIRECT3DDEVICE9 d3ddv;
	LPD3DXSPRITE spriteHandler;

	int index;								// Current sprite index
	int width;								// Sprite width
	int height;							// Sprite height
	int count;								// Number of sprites
	int spritePerRow;						// Number of sprites per row
	float x, y;
	bool backLoop;
public:
	Sprite();
	Sprite(LPDIRECT3DDEVICE9 d3ddv, char *FilePath, int SpriteWidth, int SpriteHeight, int Count, int SpritePerRow);
	void Next();
	void NextLoop();
	void NextRepeat();
	void NextEnd();
	void Reset();
	void SetIndex(int n);
	int GetIndex();
	void Render(float X, float Y, int vpx, int vpy);
	void setX(float);
	void setY(float);
	float getX();
	float getY();
	~Sprite();
};