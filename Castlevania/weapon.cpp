#include "weapon.h"


Weapon::Weapon()
{
	x = y = vx = vy = 0;
	type = 1;
	CRec = RecF(0, 0, 6, 6);
	explosion = NULL;
}


Weapon::~Weapon()
{
}

void Weapon::Destroy()
{
	x = y = vx = vy = 0;
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

bool Weapon::SetFight(bool val)
{
	fight = val;
	return fight;
}
bool Weapon::GetFight()
{
	return fight;
}

bool Weapon::SetFalling(bool val)
{
	falling = val;
	return falling;
}
bool Weapon::GetFalling()
{
	return falling;
}