#include "SmallHeart.h"

SmallHeart::SmallHeart()
{}


SmallHeart::~SmallHeart()
{}

SmallHeart::SmallHeart(LPDIRECT3DDEVICE9 d3ddv, CSimon* _simon)
{
	simon = _simon;

	smallheart = new Sprite(d3ddv, "resource\\image\\item\\0.png", 16, 16, 1, 1);
	CRec = RecF(0, 0, 16, 16);
}

void SmallHeart::Draw(float vpx, float vpy)
{
	if (visible)
	{
		if (y < (simon->GetY() - 27))
		{
			y = (simon->GetY() - 27);
		}
		smallheart->Render(x + 8, y + 8, vpx, vpy);
		if (time > 200) visible = false;
	}
		

}

void SmallHeart::Update()
{
	if (visible)
	{
		time++;
		y -= 0.3f;

	}
	CRec.x = x;
	CRec.y = y;
	CRec.width = 16;
	CRec.height = 16;
}
void SmallHeart::Destroy()
{
	time = 0;
	visible = false;
	x = y = -100;
	vx = vy = 0;
	CRec = RecF(0, 0, 0, 0);
}
