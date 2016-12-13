#include "TMXParser.h"
#include <cstdlib>
#include <iostream>
#include <sstream>

extern int Current_State;

Parser::Parser(char* filename)
{
	fileName = filename;
	fire_direct = true;
}

Parser::Parser()
{
}

Parser::~Parser()
{
}

void Parser::ReadMap(int &_width, int &_height, int* &arr, RecFList &_collisionRecs, RecFList &_ladderRecs)
{

	rapidxml::xml_document<> doc;
	rapidxml::file<> file(fileName);
	doc.parse<0>(file.data());
	//get root nodes
	root_node = doc.first_node("map");

	mapwidth = std::atoi(root_node->first_attribute("width")->value());
	mapheight = std::atoi(root_node->first_attribute("height")->value());
	int count = mapwidth*mapheight;
	arr = new int[count];
	RecFList recList;
	RecFList ladderList;

	for (rapidxml::xml_node<>* layer_node = root_node->first_node("layer"); layer_node; layer_node = layer_node->next_sibling("layer")) {
		std::string layername = layer_node->first_attribute("name")->value();
		if (layername.compare("Map") == 0)
		{
			int i = 0;
			rapidxml::xml_node<>* data_node = layer_node->first_node("data");
			for (rapidxml::xml_node<>* tile_node = data_node->first_node("tile"); tile_node; tile_node = tile_node->next_sibling("tile")){
				int gid = std::atoi(tile_node->first_attribute("gid")->value());
				arr[i] = gid;
				i++;
			}
		}
	}

	for (rapidxml::xml_node<>* oGroup_node = root_node->first_node("objectgroup"); oGroup_node; oGroup_node = oGroup_node->next_sibling("objectgroup")) {
		std::string name = oGroup_node->first_attribute("name")->value();
		if (name.compare("Collision") == 0)
		{
			for (rapidxml::xml_node<>* object_node = oGroup_node->first_node("object"); object_node; object_node = object_node->next_sibling("object")){
				int x, y, width, height;
				x = std::atoi(object_node->first_attribute("x")->value());
				y = std::atoi(object_node->first_attribute("y")->value());
				width = std::atoi(object_node->first_attribute("width")->value());
				height = std::atoi(object_node->first_attribute("height")->value());
				RecF rec(x, mapheight*TILE_SIZE - y - height, width, height);
				recList.push_back(rec);
			}
		}
	}

	for (rapidxml::xml_node<>* oGroup_node = root_node->first_node("objectgroup"); oGroup_node; oGroup_node = oGroup_node->next_sibling("objectgroup")) {
		std::string name = oGroup_node->first_attribute("name")->value();
		if (name.compare("MoveObject") == 0)
		{
			for (rapidxml::xml_node<>* object_node = oGroup_node->first_node("object"); object_node; object_node = object_node->next_sibling("object")){
				std::string o_name = object_node->first_attribute("name")->value();
				if (o_name.compare("Stair") == 0)
				{
					int x, y, width, height, type;
					char* _type;
					x = std::atoi(object_node->first_attribute("x")->value());
					y = std::atoi(object_node->first_attribute("y")->value());
					width = std::atoi(object_node->first_attribute("width")->value());
					height = std::atoi(object_node->first_attribute("height")->value());
					_type = object_node->first_attribute("type")->value();
					if (strcmp(_type, "UR") == 0) type = 0;
					if (strcmp(_type, "UL") == 0) type = 1;
					if (strcmp(_type, "DL") == 0) type = 2;
					if (strcmp(_type, "DR") == 0) type = 3;
					if (strcmp(_type, " ") == 0) type = 4;
					RecF rec(x, mapheight*TILE_SIZE - y - height, width, height, type);
					ladderList.push_back(rec);
				}
			}
		}
	}

	_width = mapwidth;
	_height = mapheight;
	_collisionRecs = recList;
	_ladderRecs = ladderList;

}
void Parser::ReadEnemy(char* ename, EnemyList& enemyList)
{
	rapidxml::xml_document<> doc;
	rapidxml::file<> file(fileName);
	doc.parse<0>(file.data());
	//get root nodes
	root_node = doc.first_node("map");
	mapwidth = std::atoi(root_node->first_attribute("width")->value());
	mapheight = std::atoi(root_node->first_attribute("height")->value());

	for (rapidxml::xml_node<>* oGroup_node = root_node->first_node("objectgroup"); oGroup_node; oGroup_node = oGroup_node->next_sibling("objectgroup")) {
		std::string name = oGroup_node->first_attribute("name")->value();
		if (name.compare("MoveObject") == 0)
		{
			for (rapidxml::xml_node<>* object_node = oGroup_node->first_node("object"); object_node; object_node = object_node->next_sibling("object")){
				std::string o_name = object_node->first_attribute("name")->value();
				if (o_name.compare(ename) == 0)
				{
					int x, y, width, height;
					x = std::atoi(object_node->first_attribute("x")->value());
					y = std::atoi(object_node->first_attribute("y")->value());
					width = std::atoi(object_node->first_attribute("width")->value());
					height = std::atoi(object_node->first_attribute("height")->value());
					if (o_name.compare("SpearKnights") == 0)
					{
						enemyList.push_back(new BlackKnight(x, mapheight*TILE_SIZE - height - y));
					}
					/*if (o_name.compare("BoneTowers") == 0)
					{
					enemyList.push_back(new DragonSkullCannon(x,  mapheight*TILE_SIZE - height - y));
					}
					if (o_name.compare("Ghosts") == 0)
					{
					enemyList.push_back(new Ghost(x,  mapheight*TILE_SIZE - height - y));
					}
					if (o_name.compare("MedusaHeads") == 0)
					{
					enemyList.push_back(new Medusa(x,  mapheight*TILE_SIZE - height - y));
					}
					if (o_name.compare("Bats") == 0)
					{
					enemyList.push_back(new VampireBat(x,  mapheight*TILE_SIZE - height - y));
					}*/
					if (o_name.compare("CandlesSmall") == 0)
					{
						enemyList.push_back(new Candle(x, mapheight*TILE_SIZE - height - y));
					}
				}
			}
		}
	}
}

void Parser::ReadGameObject(Platform** platform)
{
	rapidxml::xml_document<> doc;
	rapidxml::file<> file(fileName);
	doc.parse<0>(file.data());
	//get root nodes
	root_node = doc.first_node("map");
	mapwidth = std::atoi(root_node->first_attribute("width")->value());
	mapheight = std::atoi(root_node->first_attribute("height")->value());

	for (rapidxml::xml_node<>* oGroup_node = root_node->first_node("objectgroup"); oGroup_node; oGroup_node = oGroup_node->next_sibling("objectgroup")) {
		std::string name = oGroup_node->first_attribute("name")->value();
		if (name.compare("MoveObject") == 0)
		{
			int i = 0;
			for (rapidxml::xml_node<>* object_node = oGroup_node->first_node("object"); object_node; object_node = object_node->next_sibling("object")){
				std::string o_name = object_node->first_attribute("name")->value();
				if (o_name.compare("platform") == 0)
				{
					int x, y, width, height;
					x = std::atoi(object_node->first_attribute("x")->value());
					y = std::atoi(object_node->first_attribute("y")->value());
					width = std::atoi(object_node->first_attribute("width")->value());
					height = std::atoi(object_node->first_attribute("height")->value());
					platform[i] = new Platform(x, mapheight*TILE_SIZE - y - height, width, height);
					i++;
				}
			}
		}
	}
}

//void Parser::ReadGameObject(Bridge* bridge1, Bridge* bridge2)
//{
//	std::string version = VERSION;
//	rapidxml::xml_document<> doc;
//	rapidxml::file<> file(fileName);
//	doc.parse<0>(file.data());
//	//get root nodes
//	root_node = doc.first_node("map");
//	mapwidth = std::atoi(root_node->first_attribute("width")->value());
//	mapheight = std::atoi(root_node->first_attribute("height")->value());
//
//	for (rapidxml::xml_node<>* oGroup_node = root_node->first_node("objectgroup"); oGroup_node; oGroup_node = oGroup_node->next_sibling("objectgroup")) {
//		std::string name = oGroup_node->first_attribute("name")->value();
//		if (name.compare("MoveObject") == 0)
//		{
//			int i = 0;
//			for (rapidxml::xml_node<>* object_node = oGroup_node->first_node("object"); object_node; object_node = object_node->next_sibling("object")){
//				std::string o_name = object_node->first_attribute("name")->value();
//				if (o_name.compare("bridge") == 0)
//				{
//					int x, y;
//					x = std::atoi(object_node->first_attribute("x")->value());
//					y = std::atoi(object_node->first_attribute("y")->value());
//					if (i == 1){
//						*bridge2 = Bridge(x, y);
//					}
//					if (i == 0){
//						*bridge1 = Bridge(x, y);
//						i = 1;
//					}
//				}
//			}
//		}
//	}
//}
//
//void Parser::ReadGameObject(CapsuleList* capsule, BonuscaseList* bonuscase)
//{
//	std::string version = VERSION;
//	rapidxml::xml_document<> doc;
//	rapidxml::file<> file(fileName);
//	doc.parse<0>(file.data());
//	//get root nodes
//	root_node = doc.first_node("map");
//	mapwidth = std::atoi(root_node->first_attribute("width")->value());
//	mapheight = std::atoi(root_node->first_attribute("height")->value());
//
//	for (rapidxml::xml_node<>* oGroup_node = root_node->first_node("objectgroup"); oGroup_node; oGroup_node = oGroup_node->next_sibling("objectgroup")) {
//		std::string name = oGroup_node->first_attribute("name")->value();
//		if (name.compare("MoveObject") == 0)
//		{
//			for (rapidxml::xml_node<>* object_node = oGroup_node->first_node("object"); object_node; object_node = object_node->next_sibling("object")){
//				std::string o_name = object_node->first_attribute("name")->value();
//				if (o_name.compare("flyingCapsule") == 0)
//				{
//					int x, y;
//					char* t;
//					BonusType type = A;
//					x = std::atoi(object_node->first_attribute("x")->value());
//					y = std::atoi(object_node->first_attribute("y")->value());
//					t = object_node->first_attribute("btype")->value();
//					if (strcmp(t, "B") == 0) type = B;
//					if (strcmp(t, "F") == 0) type = F;
//					if (strcmp(t, "L") == 0) type = L;
//					if (strcmp(t, "R") == 0) type = R;
//					if (strcmp(t, "S") == 0) type = S;
//					if (strcmp(t, "M") == 0) type = M;
//					if (Current_State == 2)
//						capsule->push_back(new FlyingCapsule(x, y, type, false));
//					else capsule->push_back(new FlyingCapsule(x, y, type, true));
//				}
//				if (o_name.compare("contentFalcon") == 0)
//				{
//					int x, y;
//					char* t;
//					BonusType type = A;
//					x = std::atoi(object_node->first_attribute("x")->value());
//					y = std::atoi(object_node->first_attribute("y")->value());
//					t = object_node->first_attribute("btype")->value();
//					if (strcmp(t, "B") == 0) type = B;
//					if (strcmp(t, "F") == 0) type = F;
//					if (strcmp(t, "L") == 0) type = L;
//					if (strcmp(t, "R") == 0) type = R;
//					if (strcmp(t, "S") == 0) type = S;
//					if (strcmp(t, "M") == 0) type = M;
//					bonuscase->push_back(new BonusCase(x, y, type));
//				}
//			}
//		}
//	}
//}
