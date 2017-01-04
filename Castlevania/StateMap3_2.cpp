#include "StateMap3_2.h"

extern int Current_State;
extern bool vpMove;
extern int simonHP;
extern int Life_Simon;
extern float timemap;

StateMap3_2::StateMap3_2()
{
	d3ddv = NULL;
}

void StateMap3_2::Init(LPDIRECT3DDEVICE9 _d3ddv, DSound* _audio, Keyboard* _kbd)
{
	kbd = _kbd;
	d3ddv = _d3ddv;
	psound = new PSound(_audio);
	psound->PlayRepeat(2);
	map = new Map(d3ddv, "resource\\map\\Map3_2.bmp", "resource\\map\\Map3_2.tmx",kbd);
	simon = new CSimon(d3ddv, psound, 176, 42);
	mnstar = new MorningStar(d3ddv, simon, psound, 176, 42);
	explosion = new Explosion(d3ddv);
	door = new Door(d3ddv, simon, 1504, 127);
	bulletManager = new BulletManager(d3ddv, kbd, explosion, psound);
	enemyManager = new EnemyManager(d3ddv, "resource\\map\\Map3_2.tmx", simon, bulletManager, explosion);
	weaponManager = new WeaponManager(d3ddv, kbd, simon, explosion, psound);
	collisionManager = new CollisionManager(simon, enemyManager, bulletManager, weaponManager, mnstar, map, psound);

}

void StateMap3_2::Draw(int vpx, int vpy)
{
	d3ddv->BeginScene();
	d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 0.0f, 0);
	Render(vpx, vpy);
	d3ddv->EndScene();
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void StateMap3_2::Render(int vpx, int vpy)
{
	map->Draw(vpx, vpy);
	door->Draw(vpx, vpy);
	bulletManager->Draw(vpx, vpy);
	enemyManager->Draw(vpx, vpy);
	weaponManager->Draw(vpx, vpy);
	explosion->Draw(vpx, vpy);
	simon->Draw(vpx, vpy);
	mnstar->Draw(vpx, vpy);
}

void StateMap3_2::Update(int &vpx, int &vpy)
{
	kbd->UpdateKeyboard();
	map->Update();
	door->Update();
	simon->Update(kbd, vpx, vpy);
	mnstar->Update(kbd, vpx, vpy);
	collisionManager->ControlCollision(vpx, vpy);
	weaponManager->Update(vpx, vpy);
	enemyManager->Update();
	bulletManager->Update(vpx, vpy);
	explosion->Update();
	ViewPortUpdate(vpx, vpy);
	if (simon->GetY() >= 360 && simon->_isOnLadder == true) StateManagement::GetInstance()->SwitchState(new StateMap3_3());
	if (Life_Simon <= 0) {
		StateManagement::GetInstance()->SwitchState(new StateMainMenu());
	}
	if (timemap / 100 <= 0){
		SimonHP = 0;
		timemap = 030100.0f;
	}
}

void StateMap3_2::ViewPortUpdate(int &vpx, int &vpy)
{
	int px = simon->GetX();

	if (vpx < 0) vpx = 0;

	if (vpx > 2560) vpx = 2560;

	if (px < 1280 || px > 1804) /// move viewport & fix viewport when simon stand on platform
	{
		if (px > 265 && vpx < 2560) vpx = px - 265;
		else if (px <= 2816 && vpx >0) vpx = px - 265;
	}

	if (px > 1485 && px <= 1631) // colide with door
	{
		if (vpx < 1281 && vpMove == true)
		{
			simon->autoMove = false;
			vpx += 3;
		}
		else
		{
			vpMove = false;
		}

		if (vpMove == false && simon->allowCtrl == false) door->SetOpen(true);
		if (door->isopen == true) simon->autoMove = true;
	}

	if (px >= 1632 && simon->autoMove == false)
	{
		door->SetClose(true);
		door->SetOpen(false);
		if (door->isclose == true && vpx < 1536)
		{
			vpx += 3;
		}
		if (vpx >= 1536) simon->allowCtrl = true;
	}

}

void StateMap3_2::Exit(int &vpx, int &vpy)
{
	if (Life_Simon > 0){
		Current_State = 8;
		vpx = 513;
		vpy = 480;
	}
	else {
		Current_State = 0;
		vpx = 0;
		vpy = 480;
	}
	delete(psound);
	delete(map);
	delete(explosion);
	delete(simon);
	delete(mnstar);
	delete(weaponManager);
	delete(bulletManager);
	delete(enemyManager);
	delete(collisionManager);
}