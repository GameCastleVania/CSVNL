#include "StateMap3_3.h"

extern int Current_State;

StateMap3_3::StateMap3_3()
{
	d3ddv = NULL;
}

void StateMap3_3::Init(LPDIRECT3DDEVICE9 _d3ddv, DSound* _audio, Keyboard* _kbd)
{
	kbd = _kbd;
	d3ddv = _d3ddv;
	psound = new PSound(_audio);
	psound->PlayRepeat(2);
	map = new Map(d3ddv, "resource\\map\\Map3_3.bmp", "resource\\map\\Map3_3.tmx");
	simon = new CSimon(d3ddv, psound, 100, 42);
	explosion = new Explosion(d3ddv);
	bulletManager = new BulletManager(d3ddv, kbd, explosion, psound);
	enemyManager = new EnemyManager(d3ddv, "resource\\map\\Map3_3.tmx", simon, bulletManager, explosion);
	weaponManager = new WeaponManager(d3ddv, kbd, simon, explosion, psound);
	collisionManager = new CollisionManager(simon, enemyManager, weaponManager, map, psound);
}

void StateMap3_3::Draw(int vpx, int vpy)
{
	d3ddv->BeginScene();
	d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 0.0f, 0);
	Render(vpx, vpy);
	d3ddv->EndScene();
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void StateMap3_3::Render(int vpx, int vpy)
{
	map->Draw(vpx, vpy);
	bulletManager->Draw(vpx, vpy);
	enemyManager->Draw(vpx, vpy);
	weaponManager->Draw(vpx, vpy);
	explosion->Draw(vpx, vpy);
	simon->Draw(vpx, vpy);
}

void StateMap3_3::Update(int &vpx, int &vpy)
{
	kbd->UpdateKeyboard();
	map->Update();
	simon->Update(kbd, vpx, vpy);
	collisionManager->ControlCollision(vpx, vpy);
	weaponManager->Update(vpx, vpy);
	enemyManager->Update();
	bulletManager->Update(vpx, vpy);
	explosion->Update();
	ViewPortUpdate(vpx, vpy);
}

void StateMap3_3::ViewPortUpdate(int &vpx, int &vpy)
{
	/*int px = simon->GetX();

	if (vpx < 0) vpx = 0;

	if (vpx > 1024) vpx = 1024;
	if (px > 514)
	{
	if (px > 265 && vpx <1024) vpx = px - 265;
	else if (px <= 1280 && vpx >0) vpx = px - 265;
	}
	if (px < 450) vpx -= 2;*/
}

void StateMap3_3::Exit(int &vpx, int &vpy)
{
	Current_State = 9;
	vpx = 0;
	vpy = 0;
	delete(psound);
	delete(map);
	delete(explosion);
	delete(simon);
	delete(weaponManager);
	delete(bulletManager);
	delete(enemyManager);
	delete(collisionManager);
}