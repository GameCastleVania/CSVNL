#ifndef TMXPARSER_H
#define TMXPARSER_H


#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"

#include <string>
#include <vector>
#include <utility>
#include <map>


#include "recF.h"
#include "map.h"
#include "quadtree.h"
#include "Enemy.h"
#include "BlackKnight.h"
#include "DragonSkullCannon.h"
#include "Ghost.h"
#include "Medusa.h"
#include "VampireBat.h"
#include "Platform.h"
#include "Candle.h"
#include "Boss2.h"


#define TILE_SIZE 32

class Parser
{
private:
	char* fileName;
	int mapwidth;
	int mapheight;
	bool fire_direct;
public:
	Parser(char* filename);
	Parser();
	virtual ~Parser();

	rapidxml::xml_node<>* root_node;

	void ReadMap(int &_width, int &_height, int* &_mapArr, RecFList &_collisionRecs, RecFList &_ladderRecs);
	void ReadEnemy(char* name, EnemyList &enemyList);
	void ReadGameObject(Platform** platform);
	//void ReadGameObject(Bridge* bridge1, Bridge* bridge2);
	//void ReadGameObject(CapsuleList* capsule, BonuscaseList* bonuscase);
};

#endif // TMXPARSER_H