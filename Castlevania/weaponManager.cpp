#include "weaponManager.h"

Point* MultiVelocity(float vx, float vy);
WeaponManager::WeaponManager(LPDIRECT3DDEVICE9 _d3ddv, Keyboard* _keyboard, CSimon* _simon, Explosion* _explosion, PSound* _psound)
{
	kbd = _keyboard;
	simon = _simon;
	psound = _psound;
	timeFire = 0;
	fireRate = 10;
	bulletCount = 0;
	timeLimit = 25;
	nextbullet = 0;
	direc = RIGHT;

	bList = WeaponList();
	for (int i = 0; i < 70; i++){
		bList.push_back(new Weapon());
		playerBList.push_back(new Weapon());
	}

	axe = Axe(_d3ddv, _explosion);
	bmerang = Boomerang(_d3ddv, _explosion);
	dagger = Dagger(_d3ddv, _explosion);
	fbomb = FireBomb(_d3ddv, _explosion);
	mnstar = MorningStar(_d3ddv, _explosion);
}

WeaponManager::~WeaponManager()
{
}

void WeaponManager::Draw(int vpx, int vpy)
{
	for (int i = 0; i < playerBList.size(); i++){
		playerBList[i]->Draw(vpx, vpy);
	}
	for (int i = 0; i < bList.size(); i++){
		bList[i]->Draw(vpx, vpy);
	}
}

void WeaponManager::Update(int vpx, int vpy)
{
	//if (kbd->IsKeyDown(DIK_Z)) player->SetBulletType(Normal);
	//if (kbd->IsKeyDown(DIK_X)) player->SetBulletType(Multi);
	//if (kbd->IsKeyDown(DIK_C)) player->SetBulletType(MachineGun);
	//if (kbd->IsKeyDown(DIK_V)) player->SetBulletType(Spin);
	//if (kbd->IsKeyDown(DIK_B)) player->SetBulletType(Laser);

	////update player shoot
	//timeFire++;
	//nextbullet++;
	//if (bulletCount >= 4) bulletCount++;
	//if (bulletCount >= timeLimit) bulletCount = 0;
	//if (nextbullet > 30){
	//	bulletCount = 0;
	//	nextbullet = 0;
	//}
	//BulletType type = player->GetBulletType();
	//if (type == Normal) fireRate = 10;
	//if (type == Multi) fireRate = 25;
	//if (type == MachineGun) fireRate = 5;
	//if (type == Spin) fireRate = 5;
	//if (type == Laser) fireRate = 3;
	//PlayerShoot();

	////Update all bullet
	//for (int i = 0; i < playerBList.size(); i++)
	//{
	//	if (playerBList[i]->GetVisible()){
	//		playerBList[i]->Update();
	//		if (playerBList[i]->GetX() > vpx + 600 || playerBList[i]->GetX() < vpx || playerBList[i]->GetY() > vpy || playerBList[i]->GetY() < vpy - 500){
	//			playerBList[i]->Destroy();
	//		}
	//	}

	//	if (bList[i]->GetVisible()){
	//		bList[i]->Update();
	//		if (bList[i]->GetX() > vpx + 600 || bList[i]->GetX() < vpx || bList[i]->GetY() > vpy || bList[i]->GetY() < vpy - 500){
	//			bList[i]->Destroy();
	//		}
	//	}
	//}
}

void WeaponManager::Get(BulletType type, float x, float y, float vx, float vy, bool isPlayer)
{
	//if (isPlayer)
	//{
	//	if (type == Multi)
	//	{
	//		Point* p = MultiVelocity(vx, vy);
	//		for (int i = 0; i < 5; i++){
	//			Get(MachineGun, x, y, p[i].x, p[i].y, true);
	//		}
	//	}
	//	else
	//	{
	//		for (int i = 0; i < playerBList.size(); i++)
	//		{
	//			if (playerBList[i]->GetVisible() == false)
	//			{
	//				if (type == Normal) playerBList[i] = new BulletNormal(normal);
	//				if (type == MachineGun) playerBList[i] = new BulletMachineGun(machinegun);
	//				if (type == Laser) playerBList[i] = new BulletLaser(laser);
	//				if (type == Spin) playerBList[i] = new BulletSpin(spin);
	//				//if (type == Laser) playerBList[i]->Set(x-16, y, vx, vy, 3);
	//				//else 
	//				playerBList[i]->Set(x, y, vx, vy, 3);
	//				playerBList[i]->SetVisible(true);
	//				break;
	//			}
	//		}
	//	}
	//}
	//else
	//{
	//	for (int i = 0; i < bList.size(); i++)
	//	{
	//		if (bList[i]->GetVisible() == false)
	//		{
	//			switch (type)
	//			{
	//			case Normal:
	//				bList[i] = new BulletNormal(normal);
	//				bList[i]->Set(x, y, vx, vy, 2);
	//				bList[i]->SetVisible(true);
	//				break;
	//			case MachineGun:
	//				bList[i] = new BulletMachineGun(machinegun);
	//				bList[i]->Set(x, y, vx, vy, 2);
	//				bList[i]->SetVisible(true);
	//				break;
	//			case Gr:
	//				bList[i] = new BulletG(grenage);
	//				bList[i]->Set(x, y, vx, vy, 2);
	//				bList[i]->SetVisible(true);
	//				break;
	//			case Grm:
	//				bList[i] = new BulletGM(grenageM);
	//				bList[i]->Set(x, y, vx, vy, 2);
	//				bList[i]->SetVisible(true);
	//				break;
	//			default:
	//				break;
	//			}
	//			break;
	//		}
	//	}
	//}
}

void WeaponManager::Get(int boss, float x, float y, float vx, float vy)
{
	
}

void WeaponManager::PlayerShoot()
{
	/*if (simon->GetLRight()) direc = RIGHT;
	else direc = LEFT;
	bool up, down, left, right;
	up = kbd->IsKeyDown(DIK_UP);
	down = kbd->IsKeyDown(DIK_DOWN);
	right = kbd->IsKeyDown(DIK_RIGHT);
	left = kbd->IsKeyDown(DIK_LEFT);
	if (up) direc = UP;
	if (down && simon->GetState() == JUMP) direc = DOWN;
	if (left) direc = LEFT;
	if (right) direc = RIGHT;
	if (up && left) direc = LEFTUP;
	if (up && right) direc = RIGHTUP;
	if (down && left) direc = LEFTDOWN;
	if (down && right) direc = RIGHTDOWN;

	float x, y, vx, vy;
	x = simon->GetGunx();
	y = simon->GetGuny();
	switch (direc)
	{
	case LEFT:
		vx = -BULLET_SPEED;
		vy = 0;
		break;
	case RIGHT:
		vx = BULLET_SPEED;
		vy = 0;
		break;
	case UP:
		vx = 0;
		vy = BULLET_SPEED;
		break;
	case DOWN:
		vx = 0;
		vy = -BULLET_SPEED;
		break;
	case LEFTUP:
		vx = -BULLET_SPEED / 1.5;
		vy = BULLET_SPEED / 2;
		break;
	case LEFTDOWN:
		vx = -BULLET_SPEED / 1.5;
		vy = -BULLET_SPEED / 2;
		break;
	case RIGHTUP:
		vx = BULLET_SPEED / 1.5;
		vy = BULLET_SPEED / 2;
		break;
	case RIGHTDOWN:
		vx = BULLET_SPEED / 1.5;
		vy = -BULLET_SPEED / 2;
		break;
	default:
		break;
	}

	if (kbd->IsKeyDown(DIK_A) && timeFire >= fireRate && player->GetState() != DIVE && player->IsAlive() && bulletCount < 4)
	{
		BulletType type = player->GetBulletType();
		if (type == Multi) psound->Play(10);
		if (type == Laser) psound->Play(8);
		if (type == MachineGun) psound->Play(9);
		if (type == Normal || type == Spin) psound->Play(7);
		Get(type, x, y, vx, vy, true);
		timeFire = 0;
		bulletCount++;
	}*/
}

//void WeaponManager::SetPLayerBType(BonusType t)
//{
//	if (t == F) player->SetBulletType(Spin);
//	if (t == M) player->SetBulletType(MachineGun);
//	if (t == L) player->SetBulletType(Laser);
//	if (t == S) player->SetBulletType(Multi);
//}

WeaponList WeaponManager::GetList()
{
	return bList;
}

WeaponList WeaponManager::GetpList()
{
	return playerBList;
}

void WeaponManager::LowerTimeLimit()
{
	timeLimit -= 5;
}