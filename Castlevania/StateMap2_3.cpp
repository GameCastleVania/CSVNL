#include "StateMap2_3.h"

extern int Current_State;

StateMap2_3::StateMap2_3()
{
	d3ddv = NULL;
}

void StateMap2_3::Init(LPDIRECT3DDEVICE9 _d3ddv, DSound* _audio, Keyboard* _kbd)
{
	kbd = _kbd;
	d3ddv = _d3ddv;
	psound = new PSound(_audio);
	psound->PlayRepeat(2);
	map = new Map(d3ddv, "resource\\map\\Map2-3.bmp", "resource\\map\\Map2-3.tmx");
	simon = new CSimon(d3ddv, psound, 1680, 42);
	mstar = new MorningStar(d3ddv, simon, psound, 1680, 42);
	enemyManager = new EnemyManager(d3ddv, "resource\\map\\Map2-3.tmx", simon, bulletManager, explosion);
	collisionManager = new CollisionManager(simon, map, psound);
	weaponManager = new WeaponManager(d3ddv, kbd, simon, explosion, psound);
	Parser tmx("resource\\map\\Map2-3.tmx");// doc file map.tmx
	platform = new Platform*[2];
	tmx.ReadGameObject(platform);
	platform[0]->Init(d3ddv, 120, 2);
	platform[1]->Init(d3ddv, 120, 2);
	collisionManager->AddSpecialObjects(platform);
}

void StateMap2_3::Draw(int vpx, int vpy)
{
	d3ddv->BeginScene();
	d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 0.0f, 0);
	Render(vpx, vpy);
	d3ddv->EndScene();
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

void StateMap2_3::Render(int vpx, int vpy)
{
	map->Draw(vpx, vpy);
	simon->Draw(vpx, vpy);
	mstar->Draw(vpx, vpy);
	platform[0]->Draw(vpx, vpy);
	platform[1]->Draw(vpx, vpy);
	enemyManager->Draw(vpx, vpy);
	weaponManager->Draw(vpx, vpy);
	//bulletManager->Draw(vpx, vpy);
	//explosion->Draw(vpx, vpy);
}

void StateMap2_3::Update(int &vpx, int &vpy)
{
	kbd->UpdateKeyboard();
	map->Update();
	simon->Update(kbd, vpx, vpy);
	mstar->Update(kbd, vpx, vpy);
	platform[0]->Update();
	platform[1]->Update();
	collisionManager->ControlCollision(vpx, vpy);
	weaponManager->Update(vpx, vpy);
	//enemyManager->Update();
	//bulletManager->Update(vpx, vpy);
	//explosion->Update();
	ViewPortUpdate(vpx, vpy);
	if (simon->GetY() >= 360 && simon->isOnLadder == true) StateManagement::GetInstance()->SwitchState(new StateMap2_4());
}

void StateMap2_3::ViewPortUpdate(int &vpx, int &vpy)
{
	int px = simon->GetX();

	if (vpx < 0) vpx = 0;

	if (vpx > 2557) vpx = 2557;
	if (simon->isRightPress == true && px > 265 && vpx <2557) vpx = px - 265;
	else if (simon->isLeftPress == true && px <= 2816 && vpx >0) vpx = px - 265;
}

void StateMap2_3::Exit(int &vpx, int &vpy)
{
	Current_State = 5;
	vpx = 1024;
	vpy = 480;
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