#pragma once
#include "Item.h"
#include "simon.h"

class SmallHeart :
	public Item
{
protected:
	Sprite* smallheart;
	CSimon* simon;

public:
	SmallHeart();
	SmallHeart(LPDIRECT3DDEVICE9 d3ddv,CSimon* _simon);
	~SmallHeart();

	void Draw(float vpx, float vpy);
	void Update();
	void Destroy();
};
