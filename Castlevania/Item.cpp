#include "Item.h"
//Item----------------------------------------------------------------------------------------------
Item::Item()
{}
Item::Item(LPDIRECT3DDEVICE9 d3ddv)
{
	x = y = vx = vy = 0;
	itype = SMALLHEART;
	type = 7;
	CRec = RecF(x, y, 48, 30);
}
Item::~Item()
{
}
void Item::Draw(int vpx, int vpy)
{

}
void Item::Update()
{

}
void Item::Destroy()
{
	CRec = RecF(0, 0, 0, 0);
}
ItemType Item::GetType()
{
	return itype;
}

void Item::Set(float VX, float VY)
{
	vx = VX;
	vy = VY;
}
void Item::Set(float X, float Y, float VX, float VY)
{
	x = X;
	y = Y;
	vx = VX;
	vy = VY;
}
void Item::Set(float X, float Y, float VX, float VY, ItemType Type)
{
	x = X;
	y = Y;
	vx = VX;
	vy = VY;
	itype = Type;
}
