#include "explosion.h"

Explode::Explode()
{}

Explode::~Explode()
{}

Explode::Explode(LPDIRECT3DDEVICE9 _d3ddv, int _type, float _x, float _y)
{
	type = _type;
	x = _x;
	y = _y;
	index = 0;
	animation = 0;
	visible = false;

	type1 = new Sprite(_d3ddv, "resource\\image\\explosion\\0.bmp", 16, 20, 1, 1);
	type2 = new Sprite(_d3ddv, "resource\\image\\explosion\\1.bmp", 43, 44, 3, 3);
	type3 = new Sprite(_d3ddv, "resource\\image\\explosion\\2.bmp", 14, 28, 1, 1);
}

void Explode::Update()
{
	index++;
	type1->SetIndex(index);
	type2->SetIndex(index);

	if (index >= 3)
	{
		x = y = 0;
		visible = false;
	}

	if (type == 4) CRec = RecF(x + 5, y + 5, 54, 54);
	else CRec = RecF(0, 0, 0, 0);
}

void Explode::Draw(int vpx, int vpy)
{
	if (visible)
	{
		switch (type)
		{
		case 1:
			type1->Render(x, y, vpx, vpy);
			break;
		case 2:
			type2->Render(x, y, vpx, vpy);
			break;
		case 3:
			type3->Render(x, y, vpx, vpy);
			break;
		case 4:
			type1->Render(x, y, vpx, vpy);
			break;
		default:
			break;
		}
	}
}

bool Explode::Getvisible()
{
	return visible;
}

int Explode::GetType()
{
	return type;
}

int Explode::GetAnimation()
{
	return animation;
}

void Explode::Set(int _type, float _x, float _y, bool _visible, int _animation)
{
	type = _type;
	x = _x;
	y = _y;
	visible = _visible;
	animation = _animation;
	index = 0;
}


Explosion::Explosion()
{}

Explosion::~Explosion()
{}

Explosion::Explosion(LPDIRECT3DDEVICE9 _d3ddv)
{
	last_time = GetTickCount();
	life = 0;
	for (int i = 0; i < 50; i++)
	{
		exlist.push_back(Explode(_d3ddv, 1, 0, 0));
	}
}

void Explosion::Update()
{
	for (int i = 0; i < 50; i++)
	{
		if (exlist[i].GetAnimation() != 0){
			if (exlist[i].Getvisible() && life%exlist[i].GetAnimation() == 0) exlist[i].Update();
		}
		else if (exlist[i].Getvisible()) exlist[i].Update();
	}
	life++;
}

void Explosion::Draw(int vpx, int vpy)
{
	for (int i = 0; i < 50; i++)
	{
		if (exlist[i].Getvisible())
		{
			exlist[i].Draw(vpx, vpy);
		}
	}
}


void Explosion::Get(int _type, float _x, float _y, int _animation)
{
	for (int i = 0; i < 50; i++)
	{
		if (!exlist[i].Getvisible())
		{
			exlist[i].Set(_type, _x, _y, true, _animation);
			break;
		}
	}
}

ListExplode Explosion::GetList()
{
	ListExplode a = ListExplode();
	for (int i = 0; i < exlist.size(); i++)
	{
		if (exlist[i].Getvisible() && exlist[i].GetType() == 4)
		{
			a.push_back(exlist[i]);
		}
	}
	return a;
}