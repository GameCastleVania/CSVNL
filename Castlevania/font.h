#ifndef FONT_H
#define FONT_H

#include <d3dx9.h>
#include <iostream>
#include <string>
using namespace std;

#define FRAME_RATE 20

class Font
{
private:
	LPD3DXFONT	_font;
	RECT		_fontPosition;
	DWORD _localTime;
	bool _isDrawAnimation;
	int _frameRate;
	void _render(char* text, float x, float y, D3DCOLOR color);

	

public:
	Font(LPDIRECT3DDEVICE9 d3ddv, int size, int screenWidth, int screenHeight);
	~Font();
	void _initialize();
	void updateAnimation();
	void render(char* text, float x, float y);
	void render(int number, float x, float y);
	void renderAnimation(char* text, float x, float y, int deltaTime);
	void onLost();
};
#endif