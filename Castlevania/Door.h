#pragma once
#include "gameobject.h"
#include "simon.h"
#include "sprite.h"

class Door :
	public GameObject
{
private:
	Sprite *door1;
	Sprite *door2;
	Sprite *closedoor;
	DWORD last_time;
	CSimon* simon;

	bool open = false;// trang thai door mo
	bool close = false;// trang thai door dong
	bool isopen = false;// trang thai door da mo xong
	bool isclose = false;// trang thai door da dong xong
	int time = 0;

public:
	Door();
	Door(LPDIRECT3DDEVICE9 d3ddv, CSimon* simon, float x, float y);
	~Door();

	void Update();
	void Draw(int vpx, int vpy);
	void Destroy();

	bool GetOpen()
	{
		return open;
	}
	bool GetClose()
	{
		return close;
	}
	bool SetOpen(bool value)
	{
		return open = value;
	}
	bool SetClose(bool value)
	{
		return close = value;
	}
};

