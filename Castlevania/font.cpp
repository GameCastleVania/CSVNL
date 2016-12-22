#include "font.h"

void Font::_initialize()
{
	_localTime = 0;
	_frameRate = FRAME_RATE;
	_isDrawAnimation = true;
}

Font::Font(LPDIRECT3DDEVICE9 d3ddv, int size, int screenWidth, int screenHeight)
{
	this->_initialize();
	_fontPosition.top = 0;
	_fontPosition.left = 0;
	_fontPosition.right = screenWidth;
	_fontPosition.bottom = screenHeight;
	D3DXFONT_DESC FontDesc = {
		size,
		0,
		400,
		0,
		false,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_PITCH, "Arial" };

	//create font
	D3DXCreateFontIndirect(d3ddv, &FontDesc, &_font);
}
Font::~Font()
{
	if (_font != NULL)
	{
		_font->Release(); //release font
		_font = NULL;
	}
}

void Font::render(char* text, float x, float y)
{
	_render(text, x, y, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void Font::render(int number, float x, float y)
{
	_render((char*)to_string(number).c_str(), x, y, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void Font::updateAnimation()
{
	_isDrawAnimation = !_isDrawAnimation;
}

void Font::renderAnimation(char* text_, float x_, float y_, int deltaTime_)
{
	_localTime += deltaTime_;
	if (_localTime >= 1000 / _frameRate)
	{
		_localTime = 0;
		this->updateAnimation();
	}
	if (this->_isDrawAnimation)
		_render(text_, x_, y_, D3DCOLOR_ARGB(255, 255, 255, 255));

}

void Font::onLost()
{
	_font->OnLostDevice();
	_font->OnResetDevice();
}

void Font::_render(char* text, float x, float y, D3DCOLOR color)
{
	_fontPosition.left = x;
	_fontPosition.top = y;
	_font->DrawText(NULL,
		text,
		-1,
		&_fontPosition,
		NULL,
		color); //draw text
}