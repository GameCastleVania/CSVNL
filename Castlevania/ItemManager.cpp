#include "ItemManager.h"


//ItemManager----------------------------------------------------------------------------------------
ItemManager::ItemManager()
{}
ItemManager::ItemManager(LPDIRECT3DDEVICE9 _d3ddv)
{
	item = ItemList();
	for (int i = 0; i < 14; i++)
	{
		item.push_back(new Item(_d3ddv));
	}
}
ItemManager::~ItemManager()
{}
void ItemManager::Draw(int vpx, int vpy)
{
	for (int i = 0; i < item.size(); i++)
	{
		item[i]->Draw(vpx, vpy);
	}
}
void ItemManager::Update()
{
	for (int i = 0; i < item.size(); i++)
	{
		item[i]->Update();
	}
}
void ItemManager::Get(float X, float Y, float VX, float VY, ItemType type)
{
	for (int i = 0; i < item.size(); i++)
	{
		item[i]->Set(X, Y, VX, VY, type);
	}
}
ItemList ItemManager::GetList()
{
	return item;
}