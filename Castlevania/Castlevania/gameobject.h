#ifndef GAMEOBJECT_H
#define	GAMEOBJECT_H
#pragma once
#include <d3dx9.h>
#include "recF.h"
#include "keyboard.h"
#include "Utils.h"

class GameObject
{
protected:
	char *name;
	int id, type;
	float x, y;
	float vx, vy;
	float width, height;
	LPDIRECT3DDEVICE9 d3ddv;
public:
	RecF CRec;
	GameObject();
	GameObject(char *_name,int _id, int _type, float _x, float _y, float _width, float _height);
	~GameObject();
	
	virtual void Destroy();

	float GetX();
	float GetY();
	float GetVX();
	float GetVY();
	int GetType();

	void SetX(float X);
	void SetY(float Y);
	void SetVX(float VX);
	void SetVY(float VY);
	void SetType(int Type);
};



#endif // !GAMEOBJECT_H


