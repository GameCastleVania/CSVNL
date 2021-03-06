#include "StateMap2_4.h"

extern int Current_State;
extern int Boss2HP;
extern int Life_Simon;
extern float timemap;

StateMap2_4::StateMap2_4()
{
	d3ddv = NULL;
}

void StateMap2_4::Init(LPDIRECT3DDEVICE9 _d3ddv, DSound* _audio, Keyboard* _kbd)
{
	kbd = _kbd;
	d3ddv = _d3ddv;
	psound = new PSound(_audio);
	psound->PlayRepeat(2);
	map = new Map(d3ddv, "resource\\map\\Map2-4.bmp", "resource\\map\\Map2-4.tmx",kbd);
	simon = new CSimon(d3ddv, psound, 1360, 42);
	mnstar = new MorningStar(d3ddv, simon, psound, 1360, 42);
	explosion = new Explosion(d3ddv);
	bulletManager = new BulletManager(d3ddv, kbd, explosion, psound);
	enemyManager = new EnemyManager(d3ddv, "resource\\map\\Map2-4.tmx", simon, bulletManager, explosion);
	weaponManager = new WeaponManager(d3ddv, kbd, simon, explosion, psound);
	collisionManager = new CollisionManager(simon, enemyManager, bulletManager, weaponManager, mnstar, map, psound);
	Parser tmx("resource\\map\\Map2-4.tmx");// doc file map.tmx
}

void StateMap2_4::Draw(int vpx, int vpy)
{
	d3ddv->BeginScene();
	d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 0.0f, 0);
	Render(vpx, vpy);
	d3ddv->EndScene();
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void StateMap2_4::Render(int vpx, int vpy)
{
	map->Draw(vpx, vpy);
	bulletManager->Draw(vpx, vpy);
	enemyManager->Draw(vpx, vpy);
	weaponManager->Draw(vpx, vpy);
	explosion->Draw(vpx, vpy);
	simon->Draw(vpx, vpy);
	mnstar->Draw(vpx, vpy);
}

void StateMap2_4::Update(int &vpx, int &vpy)
{
	kbd->UpdateKeyboard();
	map->Update();
	simon->Update(kbd, vpx, vpy);
	mnstar->Update(kbd, vpx, vpy);
	collisionManager->ControlCollision(vpx, vpy);
	weaponManager->Update(vpx, vpy);
	enemyManager->Update();
	bulletManager->Update(vpx, vpy);
	explosion->Update();
	ViewPortUpdate(vpx, vpy);
	/*if (Boss2HP <= 0)
	{
		StateManagement::GetInstance()->SwitchState(new StateMap3_1());
	}*/
	if (Life_Simon <= 0) {
		StateManagement::GetInstance()->SwitchState(new StateMainMenu());
	}
	if (timemap / 100 <= 0){
		SimonHP = 0;
		timemap = 030100.0f;
	}
	
}

void StateMap2_4::ViewPortUpdate(int &vpx, int &vpy)
{
	int px = simon->GetX();

	if (vpx < 0) vpx = 0;

	if (vpx > 1024) vpx = 1024;
	if (px > 514)
	{
		if (px > 265 && vpx <1024) vpx = px - 265;
		else if (px <= 1280 && vpx >0) vpx = px - 265;
	}
	if (px < 450) vpx -= 2;
}

void StateMap2_4::Exit(int &vpx, int &vpy)
{
	if (Life_Simon > 0){
		Current_State = 6;
		vpx = 1024;
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