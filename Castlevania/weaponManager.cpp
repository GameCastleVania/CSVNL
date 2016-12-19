#include "weaponManager.h"
#include <iostream>
#include <sstream>
#define ANIMATE_RATE 2
#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}

WeaponManager::WeaponManager(LPDIRECT3DDEVICE9 _d3ddv, Keyboard* _keyboard, CSimon* _simon, Explosion* _explosion, PSound* _psound)
{
	kbd = _keyboard;
	simon = _simon;
	psound = _psound;
	direc = RIGHT;
	fight = false;
	upfight = false;
	count = 0;
	simonWList = WeaponList();
	for (int i = 0; i < 70; i++){
		simonWList.push_back(new Weapon());
	}

	axe = Axe(_d3ddv, _explosion, _simon);
	bmerang = Boomerang(_d3ddv, _explosion, _simon);
	dagger = Dagger(_d3ddv, _explosion, _simon);
	fbomb = FireBomb(_d3ddv, _explosion, _simon);
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
			count++;
			Destroy(vpx, vpy);
		}
	}

}


void WeaponManager::Update(int vpx, int vpy)
{

	if (kbd->IsKeyDown(DIK_Z)) simon->SetWeaponType(FIREBOMB);
	if (kbd->IsKeyDown(DIK_X)) simon->SetWeaponType(AXE);
	if (kbd->IsKeyDown(DIK_C)) simon->SetWeaponType(DAGGER);
	if (kbd->IsKeyDown(DIK_V)) simon->SetWeaponType(BOOMERANG);

	if (simon->allowCtrl == true)
	{
		PlayerShoot();
	}

	for (int i = 0; i < simonWList.size(); i++)
	{
		simonWList[i]->Update();
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


	if (direc == RIGHT)
	{
		switch (simon->GetWeaponType())
		{
		case DAGGER:
		{
			vx = BULLET_SPEED;
			vy = 0;
			break;
		}
		case AXE:
		{
			vx = 3;
			vy = 6;
			break;
		}
		case FIREBOMB:
		{
			vx = 2;
			vy = 4;
			break;
		}
		case BOOMERANG:
		{
			vx = 5;
			vy = 0;
			break;
		}
		default:
			break;
		}
	}
	else if (direc == LEFT)
	{
		switch (simon->GetWeaponType())
		{
		case DAGGER:
			vx = -BULLET_SPEED;
			vy = 0;
			break;
		case AXE:
		{
			vx = -3;
			vy = 6;
			break;
		}
		case FIREBOMB:
		{
			vx = -2;
			vy = 4;
			break;
		}
		case BOOMERANG:
		{
			vx = -5;
			vy = 0;
			break;
		}
		default:
			break;
		}
	}

	
	if (kbd->IsKeyDown(DIK_RETURN))
	{
		if (upfight)
		{
			fight = true;
			if (fight && count == 0)
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

	if (kbd->IsKeyUp(DIK_RETURN))
		upfight = true;
	else upfight = false;

}

void WeaponManager::Get(WeaponType type, float x, float y, float vx, float vy)
{
	for (int i = 0; i < simonWList.size(); i++)
	{
		if (simonWList[i]->GetVisible() == false)
		{
			if (type == AXE) simonWList[i] = new Axe(axe);
			if (type == DAGGER) simonWList[i] = new Dagger(dagger);
			if (type == FIREBOMB) simonWList[i] = new FireBomb(fbomb);
			if (type == BOOMERANG) simonWList[i] = new Boomerang(bmerang);

			simonWList[i]->Set(x, y, vx, vy, 6);
			simonWList[i]->SetVisible(true);
			
			simonWList[i]->SetFight(true);
			break;
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

void WeaponManager::Destroy(int vpx, int vpy)
{
	for (int i = 0; i < simonWList.size(); i++)
	{
		switch (simon->GetWeaponType())
		{
		case FIREBOMB:
		{
			if (simonWList[i]->GetX() > vpx + 480 || simonWList[i]->GetX() < vpx || simonWList[i]->GetY() < 0)
			{
				simonWList[i]->Destroy();
				count = 0;
			}
			break;
		}
		case DAGGER:
		{
			if (simonWList[i]->GetX() > vpx + 480 || simonWList[i]->GetX() < vpx)
			{
				simonWList[i]->Destroy();
				count = 0;
			}
			break;
		}
		case AXE:
		{
			if (simonWList[i]->GetX() > vpx + 480 || simonWList[i]->GetX() < vpx || simonWList[i]->GetY() < 0)
			{
				simonWList[i]->Destroy();
				count = 0;
			}
			break;
		}
		case BOOMERANG:
		{
			if (simon->GetLRight())
			{
				if (simonWList[i]->GetX() < (simon->GetX() - 40))
				{
					simonWList[i]->Destroy();
					if (upfight)
						count = 0;
				}
			}
			else if (!simon->GetLRight())
			{
				if (simonWList[i]->GetX() > (simon->GetX() + 40))
				{
					simonWList[i]->Destroy();
					if (upfight)
						count = 0;
				}
			}
			break;
		}
		default:
			break;
		}
	}
}


WeaponList WeaponManager::GetSimonWList()
{
	return simonWList;
}
