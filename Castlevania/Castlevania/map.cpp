#include"map.h"

Map::Map()
{

}

Map::~Map()
{

}

Map::Map(LPDIRECT3DDEVICE9 _d3ddv, char *spriteSheet, char *fileName)
{
	Parser tmx(fileName);
	tmx.ReadMap(_width, _height, _mapArr, _collisionRecs);
	_spriteSheet = new Sprite(_d3ddv, spriteSheet, 32, 32, 100, 10);
	tmx.ReadMap(_width, _height, _mapArr, _collisionRecs);
	animation = 0;
	////////////////
	
}

void Map::Update()
{

}

void Map::Draw(int vpx, int vpy)
{
	int i = 0;
	int posx;
	int posy;
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			posx = x * TILE_SIZE+16;
			posy = (_height - y)*TILE_SIZE - 16;
			if ((posx < vpx +550 ) && (posx >= vpx - TILE_SIZE))//khung render map
			{
				if ((posy < vpy) && (posy >= vpy - 450 - TILE_SIZE))
				{
					_spriteSheet->SetIndex(_mapArr[i]);
					_spriteSheet->Render(posx, posy, vpx, vpy);
				}
			}
			i++;
		}
	}
}

#pragma region Get_Set
int Map::Width(){
	return _width;
}
int Map::Height(){
	return _height;
}
void Map::SetMap(int width, int height, int* mapArr, RecFList collisionRecs)
{
	_width = width;
	_height = height;
	_mapArr = mapArr;
	_collisionRecs = collisionRecs;
}

RecFList Map::CRecList()
{
	return _collisionRecs;
}

#pragma endregion