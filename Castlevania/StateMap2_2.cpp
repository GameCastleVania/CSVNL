#include "StateMap2_2.h"

extern int Current_State;
extern bool vpMove;
extern int Life_Simon;
extern float timemap;

StateMap2_2::StateMap2_2()
{
	d3ddv = NULL;
}

void StateMap2_2::Init(LPDIRECT3DDEVICE9 _d3ddv, DSound* _audio, Keyboard* _kbd)
{
	kbd = _kbd;
	d3ddv = _d3ddv;
	psound = new PSound(_audio);
	psound->PlayRepeat(2);
	map = new Map(d3ddv, "resource\\map\\Map2-2.bmp", "resource\\map\\Map2-2.tmx",kbd);
	simon = new CSimon(d3ddv, psound, 2320, 42);
	mnstar = new MorningStar(d3ddv, simon, psound, 2320, 42);
	explosion = new Explosion(d3ddv);
	door = new Door(d3ddv, simon, 1484, 223);
	bulletManager = new BulletManager(d3ddv, kbd, explosion, psound);
	enemyManager = new EnemyManager(d3ddv, "resource\\map\\Map2-2.tmx", simon, bulletManager, explosion);
	weaponManager = new WeaponManager(d3ddv, kbd, simon, explosion, psound);
	collisionManager = new CollisionManager(simon, enemyManager, bulletManager, weaponManager, mnstar, map, psound);
	Parser tmx("resource\\map\\Map2-2.tmx");// doc file map.tmx
	platform = new Platform*[1];
	tmx.ReadGameObject(platform);
	platform[0]->Init(d3ddv, 60, 2);
	collisionManager->AddSpecialObjects(platform);
}

void StateMap2_2::Draw(int vpx, int vpy)
{
	d3ddv->BeginScene();
	d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 0.0f, 0);
	Render(vpx, vpy);
	d3ddv->EndScene();
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void StateMap2_2::Render(int vpx, int vpy)
{
	map->Draw(vpx, vpy);
	door->Draw(vpx, vpy);
	enemyManager->Draw(vpx, vpy);
	simon->Draw(vpx, vpy);
	mnstar->Draw(vpx, vpy);
	platform[0]->Draw(vpx, vpy);
	bulletManager->Draw(vpx, vpy);
	weaponManager->Draw(vpx, vpy);
	explosion->Draw(vpx, vpy);
	simon->Draw(vpx, vpy);
}

void StateMap2_2::Update(int &vpx, int &vpy)
{
	kbd->UpdateKeyboard();
	map->Update();
	door->Update();
	enemyManager->Update();
	simon->Update(kbd, vpx, vpy);
	mnstar->Update(kbd, vpx, vpy);
	platform[0]->Update();
	collisionManager->ControlCollision(vpx, vpy);
	weaponManager->Update(vpx, vpy);
	bulletManager->Update(vpx, vpy);
	explosion->Update();
	ViewPortUpdate(vpx, vpy);
	if (simon->GetY() >= 360 && simon->isOnLadder == true) StateManagement::GetInstance()->SwitchState(new StateMap2_3());
	if (Life_Simon <= 0) {
		StateManagement::GetInstance()->SwitchState(new StateMainMenu());
	}
	if (timemap / 100 <= 0){
		SimonHP = 0;
		timemap = 030100.0f;
	}
}

void StateMap2_2::ViewPortUpdate(int &vpx, int &vpy)
{
	int px = simon->GetX();

	if (vpx < 0) vpx = 0;

	if (vpx > 2045) vpx = 2045;

	if (px < 1287 || px > 1797) /// move viewport & fix viewport when simon stand on platform
	{
		if (px > 265 && vpx <2044) vpx = px - 265;
		else if (px <= 2304 && vpx >0) vpx = px - 265;
	}


	if (px > 1452 && px <= 1580) // colide with door
	{
		if (vpx > 1281 && vpMove == true)
		{
			simon->autoMove = false;
			vpx -= 1.5;
		}
		else
		{
			vpMove = false;
		}

		if (vpMove == false && simon->allowCtrl == false) door->SetOpen(true);
		if (door->isopen == true) simon->autoMove = true;
	}

	if (px <= 1450 && simon->autoMove == false)
	{
		door->SetClose(true);
		door->SetOpen(false);
		if (door->isclose == true && vpx > 1018)
		{
			vpx -= 1.5;
		}
		if (vpx <= 1018) simon->allowCtrl = true;
	}


}

void StateMap2_2::Exit(int &vpx, int &vpy)
{
	if (Life_Simon > 0){
		Current_State = 4;
		vpx = 1536;
		vpy = 480;
	}
	else {
		Current_State = 0;
		vpx = 0;
		vpy = 480;
	}
	delete(psound);
	delete(map);
	delete(door);
	delete(explosion);
	delete(simon);
	delete(mnstar);
	delete(weaponManager);
	delete(bulletManager);
	delete(enemyManager);
	delete(collisionManager);
}