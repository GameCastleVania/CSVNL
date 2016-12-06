#include "simon.h"

#define WALK_SPEED 2.0f
#define GROUND_Y 61

#define ANIMATE_RATE 8
#define JUMP_VELOCITY_BOOST 3.0f
#define FALLDOWN_VELOCITY_DECREASE 0.5f

CSimon::CSimon()
{

}

CSimon::CSimon(LPDIRECT3DDEVICE9 _d3ddv, PSound* _psound, int X, int Y)
{
	playerState = STAND;
	LRight = true;
	psound = _psound;
	x = X;
	y = Y;
	vx = 0;
	vy = 0;
	Init(_d3ddv);
}

CSimon::~CSimon()
{
	delete(simon_StandR);
	delete(simon_StandL);
}

void CSimon::Init(LPDIRECT3DDEVICE9 d3ddv)
{
	//load sprite simon
	simon_R = new Sprite(d3ddv, "resource\\image\\simon\\simon-right.png", 60, 66, 4, 4);
	simon_L = new Sprite(d3ddv, "resource\\image\\simon\\simon-left.png", 60, 66, 4, 4);
	simon_StandL = new Sprite(d3ddv, "resource\\image\\simon\\simon-leftS.png", 50, 66, 1, 1);
	simon_StandR = new Sprite(d3ddv, "resource\\image\\simon\\simon-rightS.png", 50, 66, 1, 1);
	simon_DieL = new Sprite(d3ddv, "resource\\image\\simon\\simon-leftdeath.png", 64, 68, 1, 1);
	simon_DieR = new Sprite(d3ddv, "resource\\image\\simon\\simon-rightdeath.png", 64, 68, 1, 1);
	simon_LadderUpL = new Sprite(d3ddv, "resource\\image\\simon\\simon-leftLCT.png", 58, 67, 2, 2);
	simon_LadderUpR = new Sprite(d3ddv, "resource\\image\\simon\\simon-rightLCT.png", 58, 67, 2, 2);
	simon_LadderDownL = new Sprite(d3ddv, "resource\\image\\simon\\simon-leftXCT.png", 58, 67, 2, 2);
	simon_LadderDownR = new Sprite(d3ddv, "resource\\image\\simon\\simon-rightXCT.png", 58, 67, 2, 2);
	simon_CrouchL = new Sprite(d3ddv, "resource\\image\\simon\\simon-leftNgoi.png", 56, 67, 1, 1);
	simon_CrouchR = new Sprite(d3ddv, "resource\\image\\simon\\simon-rightNgoi.png", 56, 67, 1, 1);
	simon_MSStandL = new Sprite(d3ddv, "resource\\image\\simon\\simon-leftRoi.png", 60, 66, 3, 3);
	simon_MSStandR = new Sprite(d3ddv, "resource\\image\\simon\\simon-rightRoi.png", 60, 66, 3, 3);
	simon_MSLadderUpL = new Sprite(d3ddv, "resource\\image\\simon\\simon-leftLCTRoi.png", 56, 67, 3, 3);
	simon_MSLadderUpR = new Sprite(d3ddv, "resource\\image\\simon\\simon-rightLCTRoi.png", 56, 67, 3, 3);
	simon_MSLadderDownL = new Sprite(d3ddv, "resource\\image\\simon\\simon-leftXCTRoi.png", 60, 66, 3, 3);
	simon_MSLadderDownR = new Sprite(d3ddv, "resource\\image\\simon\\simon-rightXCTRoi.png", 60, 66, 3, 3);
	simon_MSDownL = new Sprite(d3ddv, "resource\\image\\simon\\simon-leftNgoiRoi.png", 57, 55, 3, 3);
	simon_MSDownR = new Sprite(d3ddv, "resource\\image\\simon\\simon-rightNgoiRoi.png", 57, 55, 3, 3);
	simon_StandBack = new Sprite(d3ddv, "resource\\image\\simon\\simon-Stand.png", 51, 66, 1, 1);
	simon_FlyL = new Sprite(d3ddv, "resource\\image\\simon\\simon-leftFly.png", 57, 66, 1, 1);
	simon_FlyR = new Sprite(d3ddv, "resource\\image\\simon\\simon-rightFly.png", 57, 66, 1, 1);
	simon_JumpL = new Sprite(d3ddv, "resource\\image\\simon\\simon-leftNhay.png", 56, 66, 1, 1);
	simon_JumpR = new Sprite(d3ddv, "resource\\image\\simon\\simon-rightNhay.png", 53, 66, 1, 1);
	CRec = RecF(x - 25, y - 30, 50, 66, vx, vy);// load vi tri ban dau cho simon
	
}

void CSimon::Update(Keyboard *kbd, int vpx, int vpy)
{
	bool upPress = kbd->IsKeyDown(DIK_W);
	bool downPress = kbd->IsKeyDown(DIK_S);
	bool leftPress = kbd->IsKeyDown(DIK_A);
	bool rightPress = kbd->IsKeyDown(DIK_D);
	bool spacePress = kbd->IsKeyDown(DIK_SPACE);
	bool spaceUp = kbd->IsKeyUp(DIK_SPACE);

	//Jump Falling------------------------------------------------
	if (playerState == JUMP)
	{
		vy -= 0.12f;
		downPress = false;
	}

	//if (y < 62)
	//{
	//	vy = 0;
	//	y = 62;
	//	playerState = STAND;
	//}


	////Falling ----------------------------------------------------
	if (y > GROUND_Y)
	{
		vy -= 0.2f;
	}
	else vy = 0;

	//Screen Edge-------------------------------------------------
	if (x < vpx + 40) x = vpx + 40;

	if (x > vpx + 440) x = vpx + 440;


	// move left or right --------------------------

	if (rightPress && downPress == false && playerState != CROUCH)
	{
		if (playerState != JUMP)
		{
			playerState = RUN;
			LRight = true;
			vx = WALK_SPEED;
		}
		else vx = WALK_SPEED;

		if (playerState == JUMP)
		{
			LRight = true;
		}
	}
	else if (leftPress && downPress == false && playerState != CROUCH)
	{

		if (playerState != JUMP )
		{
			playerState = RUN;
			LRight = false;
			vx = -WALK_SPEED;
		}
		else vx = -WALK_SPEED;

		if (playerState == JUMP)
		{
			LRight = false;
		}	
	}
	else //Stand if do nothing---------------------------
	{
		if (playerState != JUMP)
		{
			playerState = STAND;
			vx = 0;
		}
		else vx = 0;
	}

	//jump left or right //fix jump continous

	if (spacePress && downPress == false && playerState != JUMP)
	{
		if (doJump == false)
		{		
			playerState = JUMP;
			vy = 7;
		}
	}

	if (spaceUp == true)
	{
		doJump = false;
	}
	else
	{
		doJump = true;
	}


	// Crouch

	if (downPress &&playerState != JUMP)
	{
		playerState = CROUCH;
		y = y - 8;
	}


			
	//Move player-------------------------------------------------
	x += vx;
	y += vy;

	//Animation on frame---------------------------------
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		if (LRight == true) 
		{
			simon_R->Next();
			simon_StandR->Next();
			simon_JumpR->Next();
			simon_CrouchR->Next();
		}
		else
		{
			simon_L->Next();
			simon_StandL->Next();
			simon_JumpL->Next();
			simon_CrouchL->Next();
		}
		last_time = now;
	}
	UpdateCRec();
}

void CSimon::Draw(int vpx, int vpy)
{
	if (LRight == true)
	{
		switch (playerState)
		{
		case STAND:
			simon_StandR->Render(x, y, vpx, vpy);
			break;
		case RUN:
			simon_R->Render(x, y, vpx, vpy);
			break;
		case JUMP:
			simon_JumpR->Render(x, y, vpx, vpy);
			break;
		case CROUCH:
			simon_CrouchR->Render(x, y, vpx, vpy);
			break;
		default:
			break;
		}
	}
	else
	{
		
		switch (playerState)
		{
		case STAND:
			simon_StandL->Render(x, y, vpx, vpy);
			break;
		case RUN:
			simon_L->Render(x, y, vpx, vpy);
			break;
		case JUMP:
			simon_JumpL->Render(x, y, vpx, vpy);
			break;
		case CROUCH:
			simon_CrouchL->Render(x, y, vpx, vpy);
			break;
		default:
			break;
		}
	}

	
}
void CSimon::UpdateCRec()
{
	if (playerState == STAND || playerState == RUN)
	{
		CRec.x = x - 10;
		CRec.y = y - 33;
		CRec.width = 50;
		CRec.height = 66;
		CRec.vx = vx;
		CRec.vy = vy;
	}
	if (playerState == JUMP)
	{
		CRec.x = x - 10;
		CRec.y = y - 10;
		CRec.width = 56;
		CRec.height = 66;
		CRec.vx = vx;
		CRec.vy = vy;
	}

	if (playerState == CROUCH)
	{
		CRec.x = x - 10;
		CRec.y = y - 10;
		CRec.width = 56;
		CRec.height = 66;
		CRec.vx = 0;
		CRec.vy = 0;
	}
}









