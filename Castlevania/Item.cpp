#include "Item.h"
//Item----------------------------------------------------------------------------------------------
Item::Item()
{}
Item::Item(LPDIRECT3DDEVICE9 d3ddv, float X, float Y, int a)
{
	x = X;
	y = Y;
	vx = vy = 0;
	type = 7;
	typerandom = a;
	visible = false;
	smallheart = new Sprite(d3ddv, "resource\\image\\item\\0.png", 16, 16, 1, 1);
	bigheart = new Sprite(d3ddv, "resource\\image\\item\\1.png", 24, 20, 1, 1);
}
Item::~Item()
{
}
void Item::Draw(int vpx, int vpy)
{
	if (visible)
	{
		switch (typerandom){
		case 1:
			smallheart->Render(x + 8, y + 8, vpx, vpy);
			break;
		case 2:
			bigheart->Render(x + 12, y + 10, vpx, vpy);
			break;
		default:
			smallheart->Render(x + 8, y + 8, vpx, vpy);
			break;
		}
	}
}
void Item::Update()
{
	if (visible)
	{
		timeitem++;
		if (timeitem > 50) visible = false;
		switch (typerandom){
		case 1:
			y -= 1.5f;
			if (timeitem > 50) visible = false;
			break;
		case 2:
			y -= 2.5f;
			if (timeitem > 50) visible = false;
			break;
		default:
			break;
		}
	}
}

void Item::Set(float X, float Y, bool Visible, int a)
{
	x = X;
	y = Y;
	typerandom = a;
	visible = Visible;
}
bool Item::GetVisible()
{
	return visible;
}

//ItemManager----------------------------------------------------------------------------------------
ItemManager::ItemManager()
{}
ItemManager::ItemManager(LPDIRECT3DDEVICE9 _d3ddv)
{
	item = ItemList();
	for (int i = 0; i < 50; i++)
	{
		item.push_back(new Item(_d3ddv, 0, 0, 1));
	}

}
ItemManager::~ItemManager()
{}
void ItemManager::Draw(int vpx, int vpy)
{
	for (int i = 0; i < 50; i++)
	{
		if (item[i]->GetVisible())
			item[i]->Draw(vpx, vpy);
	}
}
void ItemManager::Update()
{
	for (int i = 0; i < 50; i++)
	{
		if (item[i]->GetVisible())
			item[i]->Update();
	}
}
void ItemManager::Get(float X, float Y, int a)
{
	for (int i = 0; i < 50; i++)
	{
		if (item[i]->GetVisible() == false)
		{
			item[i]->Set(X, Y, true, a);
			break;
		}

	}
}
ItemList ItemManager::GetList()
{
	return item;
}

