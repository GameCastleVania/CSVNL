#include"map.h"
extern int Current_State;
extern int Stage;
extern float time = 030100.0f;

Map::Map()
{

}

Map::~Map()
{

}

Map::Map(LPDIRECT3DDEVICE9 _d3ddv, char *spriteSheet, char *fileName)
{
	Parser tmx(fileName);
	tmx.ReadMap(_width, _height, _mapArr, _collisionRecs, _ladderRecs, _doorRecs);
	_spriteSheet = new Sprite(_d3ddv, spriteSheet, 32, 32, 100, 10);
	text = new Font(_d3ddv,22,514,480);
	gameboard = new Sprite(_d3ddv, "resource\\image\\image\\blackboard.png", 520, 80,1,1);
	healthbar = new HealthBar(_d3ddv, 50, 460, 514, 480);
	if (Current_State == 2 || Current_State == 6)
	{
		time = 030100.0f;
	}
}

void Map::Update()
{	
	time -= 1.5f;	
}

void Map::Draw(int vpx, int vpy)
{
	gameboard->Render(vpx + 250, vpy - 40, vpx, vpy);
	text->render("SCORE", 5, 0);
	text->render("TIME", 230, 0);
	text->render((char*)to_string((int)time/100).c_str(), 310, 0);
	text->render("STAGE", 400, 0);
	text->render((char*)to_string(Stage).c_str(), 490, 0);
	text->render("PLAYER", 5, 30);
	healthbar->Draw(vpx, vpy);
	text->render("ENEMY", 5, 60);

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
void Map::SetMap(int width, int height, int* mapArr, RecFList collisionRecs, RecFList stairRecs, RecFList doorRecs)
{
	_width = width;
	_height = height;
	_mapArr = mapArr;
	_collisionRecs = collisionRecs;
	_ladderRecs = stairRecs;
	_doorRecs = doorRecs;
}

RecFList Map::CRecList()
{
	return _collisionRecs;
}

RecFList Map::CRecLadderList()
{
	return _ladderRecs;
}

RecFList Map::CRecDoorList()
{
	return _doorRecs;
}
#pragma endregion