#include "PSound.h"

PSound::PSound()
{}


PSound::~PSound()
{}

PSound::PSound(DSound* audio)
{
	/*main = audio->CreateSound("Data\\Sound\\MainMenu.wav");
	round1 = audio->CreateSound("Data\\Sound\\Round1.wav");
	round2 = audio->CreateSound("Data\\Sound\\Round2.wav");
	round3 = audio->CreateSound("Data\\Sound\\Round3.wav");
	player1Up = audio->CreateSound("Data\\Sound\\Player1Up.wav");
	playerDead = audio->CreateSound("Data\\Sound\\PlayerDead.wav");
	bulletDefault = audio->CreateSound("Data\\Sound\\BulletDefault.wav");
	bulletL = audio->CreateSound("Data\\Sound\\BulletL.wav");
	bulletM = audio->CreateSound("Data\\Sound\\BulletM.wav");
	bulletS = audio->CreateSound("Data\\Sound\\BulletS.wav");
	enemyAttack = audio->CreateSound("Data\\Sound\\EnemyAttack.wav");
	enemyDead = audio->CreateSound("Data\\Sound\\EnemyDead.wav");
	bridgeExplode = audio->CreateSound("Data\\Sound\\BridgeExplosion.wav");*/
}

void PSound::Play(int id)
{
	/*switch (id)
	{
	case 1:
		main.Play();
		break;
	case 2:
		round1.Play();
		break;
	case 3:
		round2.Play();
		break;
	case 4:
		round3.Play();
		break;
	case 5:
		player1Up.Play();
		break;
	case 6:
		playerDead.Play();
		break;
	case 7:
		bulletDefault.Play();
		break;
	case 8:
		bulletL.Play();
		break;
	case 9:
		bulletM.Play();
		break;
	case 10:
		bulletS.Play();
		break;
	case 11:
		enemyAttack.Play();
		break;
	case 12:
		enemyDead.Play();
		break;
	case 13:
		bridgeExplode.Play();
		break;
	default:
		break;
	}*/
}

void PSound::PlayRepeat(int id)
{
	/*switch (id)
	{
	case 1:
		main.PlayRepeat();
		break;
	case 2:
		round1.PlayRepeat();
		break;
	case 3:
		round2.PlayRepeat();
		break;
	case 4:
		round3.PlayRepeat();
		break;
	case 5:
		player1Up.PlayRepeat();
		break;
	case 6:
		playerDead.PlayRepeat();
		break;
	case 7:
		bulletDefault.PlayRepeat();
		break;
	case 8:
		bulletL.PlayRepeat();
		break;
	case 9:
		bulletM.PlayRepeat();
		break;
	case 10:
		bulletS.PlayRepeat();
		break;
	case 11:
		enemyAttack.PlayRepeat();
		break;
	case 12:
		enemyDead.PlayRepeat();
		break;
	default:
		break;
	}*/
}