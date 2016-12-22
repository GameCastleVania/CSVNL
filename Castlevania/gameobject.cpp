#include "GameObject.h"


GameObject::GameObject()
{
	type = 0;
	x = 0;
	y = 0;
	vx = 0;
	vy = 0;
	CRec = RecF(0, 0, 0, 0);
}

GameObject::GameObject(char *_name, int _id, int _type, float _x, float _y, float _width, float _height)
{
	name = _name;
	id = _id;
	type = _type;
	x = _x;
	y = _y;
	CRec = RecF(_x, _y, _width, _height);
}
GameObject::~GameObject()
{
}

void GameObject::Destroy()
{}

float GameObject::GetX()
{
	return x;
}
float GameObject::GetY()
{
	return y;
}
float GameObject::GetVX()
{
	return vx;
}
float GameObject::GetVY()
{
	return vy;
}
int GameObject::GetType()
{
	return type;
}

void GameObject::SetX(float X)
{
	x = X;
}
void GameObject::SetY(float Y)
{
	y = Y;
}
void GameObject::SetVX(float VX)
{
	vx = VX;
}
void GameObject::SetVY(float VY)
{
	vy = VY;
}
void GameObject::SetType(int Type)
{
	type = Type;
}