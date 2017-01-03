#include "StateMap3_1.h"

extern int Current_State;

StateMap3_1::StateMap3_1()
{
	d3ddv = NULL;
}

void StateMap3_1::Init(LPDIRECT3DDEVICE9 _d3ddv, DSound* _audio, Keyboard* _kbd)
{
	kbd = _kbd;
	d3ddv = _d3ddv;
	psound = new PSound(_audio);
	psound->PlayRepeat(2);
	map = new Map(d3ddv, "resource\\map\\Map3_1.bmp", "resource\\map\\Map3_1.tmx");
	simon = new CSimon(d3ddv, psound, 1440, 92);
	mnstar = new MorningStar(d3ddv, simon, psound, 1440, 92);
	explosion = new Explosion(d3ddv);
	bulletManager = new BulletManager(d3ddv, kbd, explosion, psound);
	enemyManager = new EnemyManager(d3ddv, "resource\\map\\Map3_1.tmx", simon, bulletManager, explosion);
	weaponManager = new WeaponManager(d3ddv, kbd, simon, explosion, psound);
	collisionManager = new CollisionManager(simon, enemyManager, weaponManager, map, psound);
}

void StateMap3_1::Draw(int vpx, int vpy)
{
	d3ddv->BeginScene();
	d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 0.0f, 0);
	Render(vpx, vpy);
	d3ddv->EndScene();
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void StateMap3_1::Render(int vpx, int vpy)
{
	map->Draw(vpx, vpy);
	bulletManager->Draw(vpx, vpy);
	enemyManager->Draw(vpx, vpy);
	weaponManager->Draw(vpx, vpy);
	explosion->Draw(vpx, vpy);
	simon->Draw(vpx, vpy);
	mnstar->Draw(vpx, vpy);
}

void StateMap3_1::Update(int &vpx, int &vpy)
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
	if (simon->GetY() >= 360 && simon->_isOnLadder == true) StateManagement::GetInstance()->SwitchState(new StateMap3_2());
}

void StateMap3_1::ViewPortUpdate(int &vpx, int &vpy)
{
	int px = simon->GetX();

	if (vpx < 0) vpx = 0;

	if (vpx > 1024) vpx = 1024;

	 /// move viewport & fix viewport when simon stand on platform
	if (px > 265 && vpx <1024) vpx = px - 265;
	else if (px <= 1280 && vpx >0) vpx = px - 265;

}

void StateMap3_1::Exit(int &vpx, int &vpy)
{
	Current_State = 7;
	vpx = 0;
	vpy = 480;
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