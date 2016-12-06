#include "weapon.h"


Weapon::Weapon()
{
	x = y = vx = vy = -100;
	type = 1;
	CRec = RecF(0, 0, 6, 6);
	explosion = NULL;
	visible = false;
	ex = false;
}


Weapon::~Weapon()
{
}

void Weapon::SetVisible(bool vis)
{
	visible = vis;
}

bool Weapon::GetVisible()
{
	return visible;
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
