#include "sprite.h"

Sprite::Sprite()
{}

Sprite::Sprite(LPDIRECT3DDEVICE9 D3ddv, char *FilePath, int Width, int Height, int Count, int SpritePerRow)
{
	d3ddv = D3ddv;
	D3DXCreateSprite(d3ddv, &spriteHandler);

	D3DXIMAGE_INFO info;
	HRESULT result;

	image = NULL;
	backLoop = false;

	width = Width;
	height = Height;
	count = Count;
	spritePerRow = SpritePerRow;
	index = 0;

	D3DXGetImageInfoFromFile(FilePath, &info);

	LPDIRECT3DDEVICE9 d3ddv;
	spriteHandler->GetDevice(&d3ddv);

	result = D3DXCreateTextureFromFileEx(
		d3ddv,
		FilePath,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		&info,
		NULL,
		&image);
}

Sprite::~Sprite()
{
	image->Release();
}

void Sprite::Render(float X, float Y, int vpx, int vpy)

{
	x = X;
	y = Y;
	RECT srect;

	srect.left = (index % spritePerRow)*(width);
	srect.top = (index / spritePerRow)*(height);
	srect.right = srect.left + width;
	srect.bottom = srect.top + height;

	D3DXVECTOR3 position((float)X, (float)Y, 0);

	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = -vpx;
	mt._42 = vpy;
	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &position, &mt);

	D3DXVECTOR3 p(vp_pos.x, vp_pos.y, 0);
	D3DXVECTOR3 center((float)width / 2, (float)height / 2, 0);

	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	spriteHandler->Draw(
		image,
		&srect,
		&center,
		&p,
		D3DCOLOR_XRGB(255, 255, 255)
		);
	spriteHandler->End();
}

void Sprite::Next()
{
	index = (index + count - 1) % count;
}

void Sprite::NextEnd()
{
	if (index < count)index++;
}

void Sprite::NextLoop()
{
	if (backLoop == true)
	{
		index--;
		if (index == 0)
		{
			backLoop = false;
			index++;
		}
	}
	else
	{
		index++;
		if (index == count)
		{
			backLoop = true;
			index--;
		}
	}
}

void Sprite::NextRepeat()
{
	index++;
	if (index == count)
	{
		index = 0;
	}
}

void Sprite::Reset()
{
	index = 0;
}

void Sprite::SetIndex(int n)
{
	index = n;
}

int Sprite::GetIndex()
{
	return index;
}
void Sprite::setX(float X)
{
	x = X;
}
void Sprite::setY(float Y)
{
	y = Y;
}
float Sprite::getX()
{
	return x;
}
float Sprite::getY()
{
	return y;
}