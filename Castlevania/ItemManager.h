#include "Item.h"
#include "SmallHeart.h"
#include "keyboard.h"
#include "psound.h"
#include "simon.h"
#include "utils.h"
#include <vector>

class ItemManager
{
private:
	Keyboard* kbd;
	PSound* psound;
	CSimon* simon;
	ItemList item;

	//Item type
	SmallHeart* smallheart;
	/*Sprite* boomerangitem;
	Sprite* daggeritem;
	Sprite* firebombitem;
	Sprite* cash;
	Sprite* cross;
	Sprite* ball;
	Sprite* two;
	Sprite* three;
	Sprite* time;
	Sprite* chickenleg;
	Sprite* bigheart;
	Sprite* smallheart;*/

public:
	ItemManager();
	ItemManager(LPDIRECT3DDEVICE9 _d3ddv);
	~ItemManager();

	void Draw(int vpx, int vpy);
	void Update();
	void Get(float, float, float, float, ItemType);

	ItemList GetList();
};
