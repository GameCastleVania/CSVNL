#pragma once
#include "Sound.h"
#include <vector>

class PSound
{
private:


public:
	PSound();
	PSound(DSound* dsound);
	~PSound();
	void Play(int id);
	void PlayRepeat(int id);
};

/* ID
!:main
2:round1
3:round2
4:round3
5:player1Up
6:playerDead
7:bulletDefault
8:bulletL
9:bulletM
10:bulletS
11:enemyAttack
12:enemyDead
13:bridgeexplode
*/

