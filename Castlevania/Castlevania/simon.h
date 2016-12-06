#ifndef _RECTANGLES_H_
#define _RECTANGLES_H_

#include <d3dx9.h>
#include "keyboard.h"
#include "gameobject.h"
#include "psound.h"
#include "recF.h"
#include "sprite.h"

class CSimon : public GameObject
{
private:
	PSound* psound;
	DWORD last_time;
	PlayerState playerState;

public:
	CSimon();
	CSimon(LPDIRECT3DDEVICE9 d3ddv, PSound* _psound, int X, int Y);
	~CSimon();

	bool LRight = true;
	bool doJump = false;

	void Init(LPDIRECT3DDEVICE9 d3ddv);
	void Update(Keyboard *kbd, int vpx, int vpy);
	void Draw(int vpx, int vpy);
	
	void UpdateCRec();

	
#pragma region Sprite
private: //All player sprite

	//Move sprite
	Sprite* simon_L; // di trai
	Sprite* simon_R; // di phai
	Sprite* simon_StandL; //dung trai
	Sprite* simon_StandR; // dung phai
	Sprite* simon_DieL; // chet trai
	Sprite* simon_DieR; // chet phai
	Sprite* simon_LadderUpR; // len cau thang phai
	Sprite* simon_LadderUpL; // len cau thang trai
	Sprite* simon_LadderDownR; // xuong cau thang phai
	Sprite* simon_LadderDownL; // xuong cau thang trai
	Sprite* simon_CrouchL; // ngoi trai
	Sprite* simon_CrouchR; // ngoi phai
	Sprite* simon_MSStandL; //danh roi ben trai
	Sprite* simon_MSStandR; // danh roi ben phai
	Sprite* simon_MSLadderUpL; // danh roi khi len cau thang trai
	Sprite* simon_MSLadderUpR; // danh roi khi len cau thang phai
	Sprite* simon_MSLadderDownL; // danh roi khi xuong cau thang trai
	Sprite* simon_MSLadderDownR; // danh roi khi xuong cau thang phai
	Sprite* simon_MSDownL; //danh roi khi ngoi trai
	Sprite* simon_MSDownR; //danh roi khi ngoi phai
	Sprite* simon_StandBack; //dung quay lung lai
	Sprite* simon_FlyL; //vang qua trai
	Sprite* simon_FlyR; //vang qua phai
	Sprite* simon_JumpR; // nhay qua phai
	Sprite* simon_JumpL; // nhay qua trai
#pragma endregion

#pragma region Get_Set
public: //Get & set function


	bool GetLRight()
	{
		return LRight;
	}

	PlayerState GetState()
	{
		return playerState;
	}

	void SetState(PlayerState newState)
	{
		playerState = newState;
	}
#pragma endregion 
};
#endif