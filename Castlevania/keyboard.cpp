#include "Keyboard.h"


Keyboard::Keyboard(HINSTANCE HInstance, HWND HWnd)
{
	hWnd = HWnd;
	hInstance = HInstance;
	DirectInput8Create
		(
		hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8, (VOID**)&di, NULL
		);
	di->CreateDevice(GUID_SysKeyboard, &keyBoard, NULL);
	keyBoard->SetDataFormat(&c_dfDIKeyboard);
	keyBoard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = 1024;

	keyBoard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	keyBoard->Acquire();

	for (int i = 0; i < 256; i++)
	{
		keyStates[i] = 0x00;
	}
}


Keyboard::~Keyboard()
{
	if (keyBoard)
	{
		keyBoard->Unacquire();
		keyBoard->Release();
	}

	if (di) di->Release();
}

void Keyboard::UpdateKeyboard()
{
	BYTE keys[256];
	keyBoard->GetDeviceState(256, keys);
	for (int i = 0; i < 256; i++)
	{
		keyStates[i] = keys[i];
	}
	if (IsKeyDown(DIK_ESCAPE))
	{
		PostMessage(hWnd, WM_QUIT, 0, 0);
	}
}

bool Keyboard::IsKeyDown(BYTE keyCode)
{
	return (keyStates[keyCode] & 0x80) > 0;
}

bool Keyboard::IsKeyUp(BYTE keyCode)
{
	return !((keyStates[keyCode] & 0x80) > 0);
}

