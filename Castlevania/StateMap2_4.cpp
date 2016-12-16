#include "StateMap2_4.h"

extern int Current_State;

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
	map = new Map(d3ddv, "resource\\map\\Map2-4.bmp", "resource\\map\\Map2-4.tmx");
	simon = new CSimon(d3ddv, psound, 1360, 42);
	mstar = new MorningStar(d3ddv, simon, psound, 1360, 42);
	bulletManager = new BulletManager(d3ddv, kbd, explosion, psound);
	enemyManager = new EnemyManager(d3ddv, "resource\\map\\Map2-4.tmx", simon, bulletManager, explosion);
	collisionManager = new CollisionManager(simon, map, psound);
	weaponManager = new WeaponManager(d3ddv, kbd, simon, explosion, psound);
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
	mstar->Draw(vpx, vpy);
	bulletManager->Draw(vpx, vpy);
	enemyManager->Draw(vpx, vpy);
	weaponManager->Draw(vpx, vpy);	
	//explosion->Draw(vpx, vpy);
	simon->Draw(vpx, vpy);
}

void StateMap2_4::Update(int &vpx, int &vpy)
{
	kbd->UpdateKeyboard();
	map->Update();
	simon->Update(kbd, vpx, vpy);
	mstar->Update(kbd, vpx, vpy);
	collisionManager->ControlCollision(vpx, vpy);
	weaponManager->Update(vpx, vpy);
	enemyManager->Update();
	bulletManager->Update(vpx, vpy);
	//explosion->Update();
	ViewPortUpdate(vpx, vpy);
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
	Current_State = 6;
	vpx = 0;
	vpy = 0;
	delete(psound);
	delete(map);
	//delete(explosion);
	delete(simon);
	delete(mstar);
	delete(weaponManager);
	//delete(bulletManager);
	//delete(enemyManager);
	delete(collisionManager);
}