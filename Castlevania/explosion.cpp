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
	last_time = 0;
	type1 = new Sprite(_d3ddv, "resource\\image\\explosion\\0.png", 16, 20, 1, 1);
	type2 = new Sprite(_d3ddv, "resource\\image\\explosion\\1.png", 43, 44, 3, 3);
	type3 = new Sprite(_d3ddv, "resource\\image\\explosion\\2.png", 14, 28, 1, 1);
	smallheart = new Sprite(_d3ddv, "resource\\image\\item\\0.png", 16, 16, 1, 1);
	bigheart = new Sprite(_d3ddv, "resource\\image\\item\\1.png", 24, 20, 1, 1);
	boomerangitem = new Sprite(_d3ddv, "resource\\image\\item\\8.png", 30, 28, 1, 1);
	firebombitem = new Sprite(_d3ddv, "resource\\image\\item\\9.png", 32, 32, 1, 1);
	axeitem = new Sprite(_d3ddv, "resource\\image\\item\\7.png", 30, 28, 1, 1);
	daggeritem = new Sprite(_d3ddv, "resource\\image\\item\\4.png", 32, 18, 1, 1);
	cash = new Sprite(_d3ddv, "resource\\image\\item\\2.png", 30, 30, 3, 3);
	ball = new Sprite(_d3ddv, "resource\\image\\item\\13.png", 28, 32, 2, 2);
	two = new Sprite(_d3ddv, "resource\\image\\item\\12.png", 28, 28, 1, 1);
	chickenleg = new Sprite(_d3ddv, "resource\\image\\item\\10.png", 32, 26, 1, 1);
}

void Explode::Update()
{
	if (visible)
	{
		DWORD now = GetTickCount();
		switch (type){
		case 10:
		{
			index++;

			if (now - last_time > 1000 / 10)
			{
				type2->NextRepeat();
				last_time = now;
			}
			if (index > 25) visible = false;
			break;
		}
		case 11:
		{
			index++;

			if (now - last_time > 1000 / 10)
			{
				type2->NextRepeat();
				last_time = now;
			}
			if (index > 35) visible = false;
			break;
		}
		case 12:
			if (now - last_time > 1000 /8)
			{
				ball->NextRepeat();
				last_time = now;
			}
			break;
		case 13:
			index++;
			if (index < 20){
				x += 0.8f;
				y -= 0.2f;
			}
			if (index >= 20 && index < 100){
				x -= 0.8f;
				y -= 0.2f;
			}
			if (index >= 100 && index < 180){
				x += 0.8f;
				y -= 0.2f;
			}

			y -= 1.5f;
			if (index >200) visible = false;
			break;
		case 14: case 15: case 16: case 17: case 18: case 19: case 20:
			index++;
			y -= 2.5f;
			if (index >200) visible = false;
			break;
		default:
			break;
		}

	}

	UpdateRect();
}

void Explode::UpdateRect()
{
	switch (type){
	case 10: case 11:
		CRec = RecF(0, 0, 0, 0);
		break;
	case 12:
		CRec = RecF(x, y, 28, 32);
		break;
	case 13:
		CRec = RecF(x, y, 16, 16);
		break;
	case 14:
		CRec = RecF(x, y, 24, 20);
		break;
	case 15: case 18:
		CRec = RecF(x, y, 30, 28);
		break;
	case 16:
		CRec = RecF(x, y, 32, 18);
		break;
	case 17:
		CRec = RecF(x, y, 32, 32);
		break;
	case 19:
		CRec = RecF(x, y, 30, 30);
		break;
	case 20:
		CRec = RecF(x, y, 32, 26);
		break;
	}
	
}
void Explode::Draw(int vpx, int vpy)
{
	if (visible)
	{
		switch (type)
		{
		case 10:
			if (index > 3)
				type2->Render(x - 5, y + 5, vpx, vpy);
			if (index < 7)
				type1->Render(x, y, vpx, vpy);
			break;
		case 11:
			type2->Render(x, y, vpx, vpy);
			break;
		case 12:
			ball->Render(x, y, vpx, vpy);
			break;
		case 13:
			smallheart->Render(x, y, vpx, vpy);
			break;
		case 14:
			bigheart->Render(x, y, vpx, vpy);
			break;
		case 15:
			axeitem->Render(x, y, vpx, vpy);
			break;
		case 16:
			daggeritem->Render(x, y, vpx, vpy);
			break;
		case 17:
			firebombitem->Render(x, y, vpx, vpy);
			break;
		case 18:
			boomerangitem->Render(x, y, vpx, vpy);
			break;
		case 19:
			cash->Render(x, y, vpx, vpy);
			break;
		/*case 21:
			two->Render(x, y, vpx, vpy);
			break;*/
		case 20:
			chickenleg->Render(x, y, vpx, vpy);
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
	exlist = ListExplode();
	last_time = GetTickCount();
	life = 0;
	for (int i = 0; i < 50; i++)
	{
		exlist.push_back(new Explode(_d3ddv, 1, 0, 0));
	}
}

void Explosion::Update()
{
	for (int i = 0; i < 50; i++)
	{
		if (exlist[i]->Getvisible()) exlist[i]->Update();
	}
}

void Explosion::Draw(int vpx, int vpy)
{
	for (int i = 0; i < 50; i++)
	{
		if (exlist[i]->Getvisible())
		{
			exlist[i]->Draw(vpx, vpy);
		}
	}
}


void Explosion::Get(int _type, float _x, float _y, int _animation)
{
	for (int i = 0; i < 50; i++)
	{
		if (exlist[i]->Getvisible() == false)
		{
			exlist[i]->Set(_type, _x, _y, true, _animation);
			break;
		}
	}
}

ListExplode Explosion::GetList()
{
	ListExplode a = ListExplode();
	for (int i = 0; i < exlist.size(); i++)
	{
		if (exlist[i]->Getvisible() && exlist[i]->GetType() == 3)
		{
			a.push_back(exlist[i]);
		}
	}
	return a;
}