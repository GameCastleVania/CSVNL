#include "weaponManager.h"

WeaponManager::WeaponManager(LPDIRECT3DDEVICE9 _d3ddv, Keyboard* _keyboard, CSimon* _simon, Explosion* _explosion, PSound* _psound)
{
	kbd = _keyboard;
	simon = _simon;
	psound = _psound;
	direc = RIGHT;
	fight = false;
	count = 0;

	for (int i = 0; i < 70; i++){
		simonWList.push_back(new Weapon());
	}

	axe = Axe(_d3ddv, _explosion);
	bmerang = Boomerang(_d3ddv, _explosion);
	dagger = Dagger(_d3ddv, _explosion, _simon);
	fbomb = FireBomb(_d3ddv, _explosion);
}

WeaponManager::~WeaponManager()
{
}

void WeaponManager::Draw(int vpx, int vpy)
{
	if (fight)
	{
		for (int i = 0; i < simonWList.size(); i++){
			simonWList[i]->Draw(vpx, vpy);		
		}
	}
	
}

void WeaponManager::Update(int vpx, int vpy)
{

	simon->SetWeaponType(DAGGER);

		

	PlayerShoot();

	////Update all bullet
	for (int i = 0; i < simonWList.size(); i++)
	{
		simonWList[i]->Update();
		if (simonWList[i]->GetX() > vpx + 600 || simonWList[i]->GetX() < vpx)
		{
			simonWList[i]->Destroy();
			count = 0;
		}
			
	}
		

}

void WeaponManager::Get(WeaponType type, float x, float y, float vx, float vy)
{
	for (int i = 0; i < simonWList.size(); i++)
	{
		if (type == AXE) simonWList[i] = new Axe(axe);
		if (type == BOOMERANG) simonWList[i] = new Boomerang(bmerang);
		if (type == DAGGER) simonWList[i] = new Dagger(dagger);
		if (type == FIREBOMB) simonWList[i] = new FireBomb(fbomb);

		simonWList[i]->SetFight(true);
		simonWList[i]->Set(x, y, vx, vy, 2);
		break;
	}
}

void WeaponManager::PlayerShoot()
{
	if (simon->GetLRight()) direc = RIGHT;
	else direc = LEFT;

	bool left, right;

	right = kbd->IsKeyDown(DIK_D);
	left = kbd->IsKeyDown(DIK_A);

	if (left) direc = LEFT;
	if (right) direc = RIGHT;

	float x, y, vx, vy;
	x = simon->GetWeaponx();
	y = simon->GetWeapony();

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
	default:
		break;
	}

	if (kbd->IsKeyDown(DIK_RETURN))
	{
		if (count == 0) fight = true;
		if (fight)
		{
			WeaponType type = simon->GetWeaponType();
			/*if (type == Multi) psound->Play(10);
			if (type == Laser) psound->Play(8);
			if (type == MachineGun) psound->Play(9);
			if (type == Normal || type == Spin) psound->Play(7);*/
			Get(type, x, y, vx, vy);
		}
		
	}
}

//void WeaponManager::SetPLayerBType(BonusType t)
//{
//	if (t == F) player->SetBulletType(Spin);
//	if (t == M) player->SetBulletType(MachineGun);
//	if (t == L) player->SetBulletType(Laser);
//	if (t == S) player->SetBulletType(Multi);
//}


WeaponList WeaponManager::GetSimonWList()
{
	return simonWList;
}

void WeaponManager::LowerTimeLimit()
{
	//timeLimit -= 5;
}