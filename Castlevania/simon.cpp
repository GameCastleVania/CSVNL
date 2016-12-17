#include "simon.h"

#define WALK_SPEED 2.0f
#define GROUND_Y 61

#define ANIMATE_RATE 8
#define ANIMATE_RATE_W 10
#define JUMP_VELOCITY_BOOST 3.0f
#define FALLDOWN_VELOCITY_DECREASE 0.5f

extern int Current_State;
extern float SimonHP;

CSimon::CSimon()
{

}

CSimon::CSimon(LPDIRECT3DDEVICE9 _d3ddv, PSound* _psound, float X, float Y)
{
	switch (Current_State)
	{
	case 2:
		playerState = STAND;
		LRight = true;
		isOnLadder = false;
		break;
	case 3:
		playerState = STANDUR;
		LRight = true;
		isOnLadder = true;
		break;
	case 4:
		playerState = STANDUR;
		LRight = true;
		isOnLadder = true;
		break;
	case 5:
		playerState = STANDUR;
		LRight = true;
		isOnLadder = true;
		break;
	default:
		break;
	}

	psound = _psound;
	fight = false;
	alive = true;
	heightJump = 0;
	HP = SimonHP;

	last_time = 0;
	_last_time = 0;
	x = X;
	y = Y;
	vx = 0;
	vy = 0;
	wpx = x;
	wpy = y;
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
	simon_StandL = new Sprite(d3ddv, "resource\\image\\simon\\simon-leftS.png", 60, 66, 1, 1);
	simon_StandR = new Sprite(d3ddv, "resource\\image\\simon\\simon-rightS.png", 60, 66, 1, 1);
	simon_DieL = new Sprite(d3ddv, "resource\\image\\simon\\simon-leftdeath.png", 64, 68, 1, 1);
	simon_DieR = new Sprite(d3ddv, "resource\\image\\simon\\simon-rightdeath.png", 64, 68, 1, 1);
	simon_StandUR = new Sprite(d3ddv, "resource\\image\\simon\\simon-StandURCT.png", 56, 66, 1, 1);
	simon_StandDL = new Sprite(d3ddv, "resource\\image\\simon\\simon-StandDLCT.png", 56, 66, 1, 1);
	simon_LadderUpL = new Sprite(d3ddv, "resource\\image\\simon\\simon-leftLCT.png", 58, 66, 2, 2);
	simon_LadderUpR = new Sprite(d3ddv, "resource\\image\\simon\\simon-rightLCT.png", 58, 66, 2, 2);
	simon_LadderDownL = new Sprite(d3ddv, "resource\\image\\simon\\simon-leftXCT.png", 58, 66, 2, 2);
	simon_LadderDownR = new Sprite(d3ddv, "resource\\image\\simon\\simon-rightXCT.png", 58, 66, 2, 2);
	simon_CrouchL = new Sprite(d3ddv, "resource\\image\\simon\\simon-leftNgoi.png", 56, 67, 1, 1);
	simon_CrouchR = new Sprite(d3ddv, "resource\\image\\simon\\simon-rightNgoi.png", 56, 67, 1, 1);
	simon_MSStandL = new Sprite(d3ddv, "resource\\image\\simon\\simon-leftRoi.png", 60, 66, 3, 3);
	simon_MSStandR = new Sprite(d3ddv, "resource\\image\\simon\\simon-rightRoi.png", 60, 66, 3, 3);
	simon_MSLadderUpL = new Sprite(d3ddv, "resource\\image\\simon\\simon-leftLCTRoi.png", 56, 67, 3, 3);
	simon_MSLadderUpR = new Sprite(d3ddv, "resource\\image\\simon\\simon-rightLCTRoi.png", 56, 67, 3, 3);
	simon_MSLadderDownL = new Sprite(d3ddv, "resource\\image\\simon\\simon-leftXCTRoi.png", 60, 66, 3, 3);
	simon_MSLadderDownR = new Sprite(d3ddv, "resource\\image\\simon\\simon-rightXCTRoi.png", 60, 66, 3, 3);
	simon_MSCrouchL = new Sprite(d3ddv, "resource\\image\\simon\\simon-leftNgoiRoi.png", 57, 55, 3, 3);
	simon_MSCrouchR = new Sprite(d3ddv, "resource\\image\\simon\\simon-rightNgoiRoi.png", 56, 66, 3, 3);
	simon_StandBack = new Sprite(d3ddv, "resource\\image\\simon\\simon-Stand.png", 51, 66, 1, 1);
	simon_FlyL = new Sprite(d3ddv, "resource\\image\\simon\\simon-leftFly.png", 57, 66, 1, 1);
	simon_FlyR = new Sprite(d3ddv, "resource\\image\\simon\\simon-rightFly.png", 57, 66, 1, 1);
	simon_JumpL = new Sprite(d3ddv, "resource\\image\\simon\\simon-leftNhay.png", 56, 67, 1, 1);
	simon_JumpR = new Sprite(d3ddv, "resource\\image\\simon\\simon-rightNhay.png", 53, 67, 1, 1);
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
	bool fightPress = kbd->IsKeyDown(DIK_K);
	bool fightUp = kbd->IsKeyUp(DIK_K);
	bool enterPress = kbd->IsKeyDown(DIK_RETURN);
	bool enterUp = kbd->IsKeyUp(DIK_RETURN);

	//Jump Falling------------------------------------------------
	if (playerState == JUMP)
	{
		vy -= 0.12f;
	}

	/*if (y < 62)
	{
	vy = 0;
	y = 62;
	playerState = STAND;
	}*/


	////Falling ----------------------------------------------------
	if (playerState != RUNUPR && playerState != STANDUR)
	{
		if (y > 62)
		{
			vy -= 0.2f;
		}
		else vy = 0;
	}

	if (isJumpRight == true || isJumpLeft == true)
	{
		heightJump += 7;
		if (heightJump > 60)
		{
			vy -= 0.1f;
		}

	}


	////Screen Edge-------------------------------------------------
	if (x >= vpx + 500) x = vpx + 500;


	//Map edge----------------------------------------------------
	
	if (Current_State == 5)
	{
		if (x <= 0) x = 0;
		if (x > 513 && vpx == 0) x = 450;
	}

	if (autoMove == true && allowCtrl == false) simonAutoMove();
	if (allowCtrl == true && autoMove == false)
	{

		// move left or right --------------------------
		if (isJumpRight == false && isJumpLeft == false)
		{
			if (rightPress && isOnLadder == false && isJumpLeft == false
				&& !fightPress && !enterPress && playerState != CROUCH  && playerState != STANDW)
			{
				if (playerState != JUMP  && isJumpRight == false)
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
			else
				if (leftPress && isOnLadder == false && isJumpRight == false
					&& !fightPress && !enterPress && playerState != CROUCH  && playerState != STANDW)
				{

					if (playerState != JUMP && isJumpLeft == false)
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
					if (playerState != JUMP && playerState != STANDUR && playerState != RUNUPR)
					{
						if (!doFight)
							playerState = STAND;
						vx = 0;
					}
					else vx = 0;
				}
		}


		///////////// move up on ladder
		if (rightPress && downPress == false && upPress == true && isOnLadder == true && playerState != CROUCH)
		{
			vx = 0.95f;
			vy = 1.0f;
			playerState = RUNUPR;
			isOnLadder = true;
			LRight = true;
		}
		else if ((rightPress == false || upPress == false) && isOnLadder == true && LRight == true)
		{
			vx = 0;
			vy = 0;
			playerState = STANDUR;
		}
		/////////// move down on ladder
		if (leftPress && downPress == true && upPress == false && isOnLadder == true && playerState != CROUCH)
		{
			vx = -0.95f;
			vy = -0.9f;
			playerState = RUNDOWNL;
			isOnLadder = true;
			LRight = false;
		}
		else if ((leftPress == false || downPress == false) && isOnLadder == true && LRight == false)
		{
			vx = 0;
			vy = 0;
			playerState = STANDDL;
		}

		if (rightPress == false) isRightPress = false;
		else isRightPress = true;

		if (leftPress == false) isLeftPress = false;
		else isLeftPress = true;



		//jump left or right //fix jump continous

		if (spacePress && downPress == false && upPress == false && isOnLadder == false
			&& playerState != JUMP && (playerState == STAND || playerState == RUN) && fightPress == false)
		{
			if (doJump == false)
			{
				if (LRight == true)
				{
					heightJump = 0;
					playerState = JUMP;
					vy = 7;
					isJumpRight = true;
					isJumpLeft = false;
					leftPress = false;
				}
				else
				{
					heightJump = 0;
					playerState = JUMP;
					vy = 7;
					isJumpRight = false;
					isJumpLeft = true;
					rightPress = false;
				}

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


		/// stand fight------------------------------------------------

		//Fight

		if ((fightPress || enterPress) && doFight == false && isfightUP == true)
		{
			doFight = true;
			isfightUP = false;
			if (simon_MSStandR->GetIndex() == 3) simon_MSStandR->SetIndex(0);
			if (simon_MSStandL->GetIndex() == 3) simon_MSStandL->SetIndex(0);
			playerState = STANDW;
		}

		if (fightUp == true && enterUp == true)
		{
			isfightUP = true;
		}
		else isfightUP = false;


		// Crouch---------------------------------------------------

		if (downPress && playerState != JUMP && playerState != RUN
			&& isOnLadder == false && isOnGround == true)
		{
			if (playerState != JUMP)
				playerState = CROUCH;
			else playerState = JUMP;
		}

		//Crouch fight
		if ((fightPress || enterPress) && downPress && playerState != JUMP
			&& isOnLadder == false && isJumpLeft == false && isJumpRight == false)
		{
			if (playerState != JUMP)
				playerState = CROUCHW;
			else playerState = JUMP;
		}
	}


	//LadderUp ------------------------------------------

	if (upPress && playerState != CROUCH && playerState != JUMP)
	{
		isUpPress = true;
	}
	else isUpPress = false;

	//LadderDown

	if (downPress && playerState != CROUCH && playerState != JUMP)
	{
		isDownPress = true;
	}
	else isDownPress = false;

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
			simon_MSCrouchR->Next();
		}
		else
		{
			simon_L->Next();
			simon_StandL->Next();
			simon_JumpL->Next();
			simon_CrouchL->Next();
			simon_MSCrouchL->Next();
		}
		last_time = now;
	}
	DWORD _now = GetTickCount();
	if (_now - _last_time > 1000 / ANIMATE_RATE_W)
	{
		if (LRight && doFight)
		{
			if (simon_MSStandR->GetIndex() == 2)
			{
				doFight = false;
				playerState = STAND;
			}
			simon_MSStandR->NextEnd();
		}
		else if (!LRight && doFight)
		{
			if (simon_MSStandL->GetIndex() == 2)
			{
				doFight = false;
				playerState = STAND;
			}
			simon_MSStandL->NextEnd();
		}
		_last_time = _now;
	}

	DWORD __now = GetTickCount();
	if (__now - __last_time > 1000 / 7.0f)
	{
		if (LRight == true)
		{
			simon_StandUR->Next();
			simon_LadderUpR->Next();
		}
		else
		{
			simon_StandDL->Next();
			simon_LadderDownL->Next();
		}
		__last_time = __now;
	}

	UpdateGunPoint();
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
		case CROUCHW:
			simon_MSCrouchR->Render(x, y, vpx, vpy);
			break;
		case STANDW:
			simon_MSStandR->Render(x, y, vpx, vpy);
			break;
		case JUMPW:
			simon_MSStandR->Render(x, y, vpx, vpy);
			break;
		case RUNUPR:
			simon_LadderUpR->Render(x, y, vpx, vpy);
			break;
		case STANDUR:
			simon_StandUR->Render(x, y, vpx, vpy);
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
		case CROUCHW:
			simon_MSCrouchL->Render(x, y, vpx, vpy);
			break;
		case STANDW:
			simon_MSStandL->Render(x, y, vpx, vpy);
			break;
		case JUMPW:
			simon_MSStandL->Render(x, y, vpx, vpy);
			break;
		case RUNDOWNL:
			simon_LadderDownL->Render(x, y, vpx, vpy);
			break;
		case STANDDL:
			simon_StandDL->Render(x, y, vpx, vpy);
			break;
		default:
			break;
		}
	}
}

void CSimon::UpdateGunPoint()
{
	if (LRight == true)
	{
		switch (playerState)
		{
		case STAND:
			wpx = x + 10;
			wpy = y;
			break;
		case RUN:
			wpx = x + 10;
			wpy = y;
			break;
		case JUMP:
			wpx = x + 10;
			wpy = y - 10;
			break;
		case CROUCH:
			wpx = x + 10;
			wpy = y - 10;
			break;
		}

	}
	else
	{
		switch (playerState)
		{
		case STAND:
			wpx = x - 10;
			wpy = y;
			break;
		case RUN:
			wpx = x - 10;
			wpy = y;
			break;
		case JUMP:
			wpx = x - 10;
			wpy = y - 10;
			break;
		case CROUCH:
			wpx = x - 10;
			wpy = y - 10;
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
		CRec.y = y - 33;
		CRec.width = 56;
		CRec.height = 66;
		CRec.vx = vx;
		CRec.vy = vy;
	}

	if (playerState == CROUCH)
	{
		CRec.x = x - 28;
		CRec.y = y - 33;
		CRec.width = 56;
		CRec.height = 66;
		CRec.vx = 0;
		CRec.vy = 0;
	}

	if (playerState == RUNUPR || playerState == STANDUR || playerState == RUNDOWNL || playerState == STANDDL)
	{
		CRec.x = x - 10;
		CRec.y = y - 33;
		CRec.width = 58;
		CRec.height = 66;
		CRec.vx = 0;
		CRec.vy = 0;
	}

	if (playerState == STANDW || playerState == JUMPW)
	{
		CRec.x = x - 10;
		CRec.y = y - 33;
		CRec.width = 60;
		CRec.height = 66;
		CRec.vx = 0;
		CRec.vy = 0;
	}
}

void CSimon::simonAutoMove()
{
	if (x > 1450 && x <= 1580 && autoMove == true)
	{
		LRight = false;
		playerState = RUN;
		vx = -1.2f;

	}
	else if (x <= 1450)
	{
		vx = 0;
		playerState = STAND;
		autoMove = false;
	}
}








