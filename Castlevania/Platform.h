#pragma once
#include "gameobject.h"
#include "sprite.h"

class Platform :
	public GameObject
{
private:
	Sprite* platForm;
	float left, right;
	bool LRight;
	int speed;
	bool moved;
	DWORD last_time;
public:
	Platform();
	Platform(float x, float y, float width, float height);
	~Platform();
	void Init(LPDIRECT3DDEVICE9 d3ddv, int range, float speed);
	void Draw(int vpx, int vpy);
	void Update();
	bool IsMoved();
};

