#pragma once
#include <dinput.h>


class Keyboard
{
private:
	HWND hWnd;
	HINSTANCE hInstance;	// Handle of the game instance
	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 keyBoard;	// The keyboard device 
	DIDEVICEOBJECTDATA keyEvents[1024];

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
public:
	Keyboard(){}
	Keyboard(HINSTANCE HInstance, HWND hWnd);
	~Keyboard();
	void UpdateKeyboard();
	bool IsKeyDown(BYTE keyCode);
	bool IsKeyUp(BYTE keyCode);
};

