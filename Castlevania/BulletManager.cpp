#include "BulletManager.h"

BulletManager::BulletManager(LPDIRECT3DDEVICE9 _d3ddv, Keyboard* _keyboard, Explosion* _explosion, PSound* _psound)
{
	kbd = _keyboard;
	psound = _psound;
	timeFire = 0;
	fireRate = 10;
	timeLimit = 25;
	nextbullet = 0;
	direc = RIGHT;

	bList = BulletList();
	for (int i = 0; i < 10; i++) {
		bList.push_back(new Bullet());
		bossBList.push_back(new Bullet());
	}

	fireball = FireBall(_d3ddv, _explosion);
	boss2Bullet = Boss2Bullet(_d3ddv);
}

BulletManager::~BulletManager()
{
}

void BulletManager::Draw(int vpx, int vpy)
{
	
	for (int i = 0; i < bList.size(); i++) {
		bList[i]->Draw(vpx, vpy);
	}
	for (int i = 0; i < bossBList.size(); i++){
	bossBList[i]->Draw(vpx, vpy);
	}
}

void BulletManager::Update(int vpx, int vpy)
{
	//Update all bullet
	for (int i = 0; i < bList.size(); i++)
	{

		if (bList[i]->GetVisible()) {
			bList[i]->Update();
			if (bList[i]->GetX() > vpx + 600 || bList[i]->GetX() < vpx || bList[i]->GetY() > vpy || bList[i]->GetY() < vpy - 500) {
				bList[i]->Destroy();
			}
		}
	}
	for (int i = 0; i < bList.size(); i++)
	{
		if (bossBList[i]->GetVisible()) {
			bossBList[i]->Update();
			if (bossBList[i]->GetX() > vpx + 600 || bossBList[i]->GetX() < vpx || bossBList[i]->GetY() > vpy || bossBList[i]->GetY() < vpy - 500) {
				bossBList[i]->Destroy();
			}
		}
	}
}

void BulletManager::Get(BulletType type, float x, float y, float vx, float vy, bool isPlayer)
{
	for (int i = 0; i < bList.size(); i++)
	{
		if (bList[i]->GetVisible() == false)
		{
			switch (type)
			{
			case Fire_ball:
				bList[i] = new FireBall(fireball);
				bList[i]->Set(x, y, vx, vy, 5);
				bList[i]->SetVisible(true);
				break;
			default:
				break;
			}
			break;
		}
	}
}

void BulletManager::Get(int boss, float x, float y, float vx, float vy )
{
	for (int i = 0; i < bossBList.size(); i++)
	{
		if (bossBList[i]->GetVisible() == false)
		{
			if (boss == 2) bossBList[i] = new Boss2Bullet(boss2Bullet);
			bossBList[i]->Set(x, y, vx, vy, 5);
			bossBList[i]->SetVisible(true);
			break;
		}
	}
}

BulletList BulletManager::GetList()
{
	return bList;
}

BulletList BulletManager::GetBossList()
{
	return bossBList;
}

float dr(int goc)
{
	return (float(goc)*3.14) / 180;
}

void BulletManager::LowerTimeLimit()
{
	timeLimit -= 5;
}