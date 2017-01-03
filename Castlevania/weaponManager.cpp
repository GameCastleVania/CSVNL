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

extern int count2w;
extern int countw;

WeaponManager::WeaponManager(LPDIRECT3DDEVICE9 _d3ddv, Keyboard* _keyboard, CSimon* _simon, Explosion* _explosion, PSound* _psound)
{
	kbd = _keyboard;
	simon = _simon;
	psound = _psound;
	direc = RIGHT;
	upfight = false;
	up2nd = false;
	simonWList = WeaponList();
	for (int i = 0; i < 50; i++){
		simonWList.push_back(new Weapon());
	}

	//simon->SetWeaponType(MORNINGSTAR);

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
	for (int i = 0; i < simonWList.size(); i++)
	{
		simonWList[i]->Draw(vpx, vpy);
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
		if (simonWList[i]->GetVisible())
		{
			simonWList[i]->Update();

			switch (simon->GetWeaponType())
			{
			case FIREBOMB:
			{
				if (simonWList[i]->GetX() > vpx + 480 || simonWList[i]->GetX() < vpx || simonWList[i]->GetY() < 0)
				{
					simonWList[i]->Destroy();
					if (count2w == -1) count2w = 2;
					if (count2w == 1) count2w = 2;
					if (count2w == 0) count2w = -1;


				}
				break;
			}
			case DAGGER:
			{
				if (simonWList[i]->GetX() > vpx + 480 || simonWList[i]->GetX() < vpx)
				{
					simonWList[i]->Destroy();
					if (count2w == -1) count2w = 2;
					if (count2w == 1) count2w = 2;
					if (count2w == 0) count2w = -1;
				}
				break;
			}
			case AXE:
			{
				if (simonWList[i]->GetX() > vpx + 480 || simonWList[i]->GetX() < vpx || simonWList[i]->GetY() < 0)
				{
					simonWList[i]->Destroy();
					if (count2w == -1) count2w = 2;
					if (count2w == 1) count2w = 2;
					if (count2w == 0) count2w = -1;
				}
				break;
			}
			case BOOMERANG:
			{
				if ((simonWList[i]->GetX() > vpx + 580 && simonWList[i]->GetFalling() == true) || 
					(simonWList[i]->GetX() < vpx - 100 && simonWList[i]->GetFalling() == true) ||
					(simonWList[i]->GetX() > simon->GetX() - 5 && simonWList[i]->GetX() < simon->GetX() + 5 && 
					simonWList[i]->GetY() > simon->GetY() - 14 && simonWList[i]->GetY() < simon->GetY() + 14))
					{
						simonWList[i]->Destroy();
						if (count2w == -1) count2w = 2;
						if (count2w == 1) count2w = 2;
						if (count2w == 0) count2w = -1;
					}
				break;
			}			
			default:
				break;
			}
		}
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
	x = simon->GetX();
	y = simon->GetY();


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

	if (kbd->IsKeyDown(DIK_K))
	{
		if (up2nd)
		{
			if (count2w == 1 || count2w == 2)
			{
				WeaponType type = simon->GetWeaponType();
				Get(type, x, y, vx, vy);
				if (count2w == 2) count2w = 1;
				else if (count2w == 1) count2w = 0;
				//DBOUT(count << endl);
			}
		}
	}
	//else if (kbd->IsKeyDown(DIK_RETURN))
	//{
	//	if (upfight)
	//	{
	//		if (countw == 0)
	//			Get(MORNINGSTAR, x, y, vx, vy);
	//		//WeaponType type = simon->GetWeaponType();
	//		
	//		//psound->Play(10);			
	//	}
	//}


	if (kbd->IsKeyUp(DIK_K)){
		up2nd = true;
		//simon->SetWeaponType(MORNINGSTAR);
	}
	else up2nd = false;

	/*if (kbd->IsKeyUp(DIK_RETURN)){
		upfight = true;
	}
	else upfight = false;*/
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
			//if (type == MORNINGSTAR) simonWList[i] = new MorningStar(mnstar);

			simonWList[i]->Set(x, y, vx, vy, 6);
			simonWList[i]->SetVisible(true);
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


WeaponList WeaponManager::GetSimonWList()
{
	return simonWList;
}
