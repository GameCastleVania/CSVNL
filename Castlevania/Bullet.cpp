#include "Bullet.h"


Bullet::Bullet()
{
	x = y = vx = vy = -100;
	type = 5;
	CRec = RecF(0, 0, 6, 6);
	explosion = NULL;
	visible = false;
	ex = false;
}


Bullet::~Bullet()
{
}

void Bullet::SetVisible(bool vis)
{
	visible = vis;
}

bool Bullet::GetVisible()
{
	return visible;
}

void Bullet::Destroy()
{
	visible = false;
	x = y = vx = vy = -100;
}


void Bullet::Set(float X, float Y, float VX, float VY)
{
	x = X;
	y = Y;
	vx = VX;
	vy = VY;
}

void Bullet::Set(float X, float Y, float VX, float VY, int Type)
{
	PosX = x = X;
	PosY = y = Y;
	vx = VX;
	vy = VY;
	type = Type;
}


bool Bullet::CanExplode()
{
	return ex;
}

void Bullet::Draw(float vpx, float vpy)
{}

void Bullet::Update()
{}
