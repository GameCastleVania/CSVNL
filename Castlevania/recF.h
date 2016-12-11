#pragma once
#include <vector>
#include <list>
using namespace std;
class RecF
{
public:
	float x, y;
	float vx, vy;
	float width, height;
	float collisionTime;
	int type;

	RecF();
	RecF(float x, float y, float width, float height, float vx = 0, float vy = 0);
	RecF(float x, float y, float width, float height, int type, float vx = 0, float vy = 0);
	~RecF();
	void Tranlate(float dx, float dy);
	static bool OverLapse(RecF a, RecF b);

	static bool AABBCheck(RecF b1, RecF b2);
	static bool AABB(RecF b1, RecF b2, float& moveX, float& moveY);
	static RecF GetSweptBroadphaseRec(RecF b);
	static float SweptAABB(RecF b1, RecF b2, float& normalx, float& normaly);
	static int Collide(RecF Rec, RecF block);
};
typedef vector <RecF> RecFList;


