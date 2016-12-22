#include "weapon.h"


Weapon::Weapon()
{
	x = y = vx = vy = -100;
	type = 6;
	CRec = RecF(0, 0, 32, 18);
	visible = false;
	explosion = NULL;
}


Weapon::~Weapon()
{
}

void Weapon::Destroy()
{
	visible = false;
	x = y = vx = vy = -100;
}


void Weapon::Set(float X, float Y, float VX, float VY)
{
	x = X;
	y = Y;
	vx = VX;
	vy = VY;
}

void Weapon::Set(float X, float Y, float VX, float VY, int Type)
{
	x = X;
	y = Y;
	vx = VX;
	vy = VY;
	type = Type;
}

bool Weapon::CanExplode()
{
	return ex;
}

void Weapon::Draw(float vpx, float vpy)
{}

void Weapon::Update()
{}

bool Weapon::SetFalling(bool val)
{
	falling = val;
	return falling;
}
bool Weapon::GetFalling()
{
	return falling;
}

void Weapon::SetVisible(bool vis)
{
	visible = vis;
}

bool Weapon::GetVisible()
{
	return visible;
}