#pragma once

///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////
#define DIRECTINPUT_VERSION 0x0800

/////////////
// LINKING //
/////////////
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

//////////////
// INCLUDES //
//////////////
#include <dinput.h>

class Input
{
public:

	Input();
	Input(const Input&);
	~Input();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

	bool IsEscapePressed();

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);

	bool IsKeyDown(unsigned int);

	float GetPosX();
	float GetPosY();
	bool IsKeyPressed();

private:
	bool keyPressed;
	float positionX, positionY;
	bool ReadKeyboard();
	void ProcessInput();
	float step;

private:
	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;

	unsigned char m_keyboardState[256];
	bool m_keys[256];

	int m_screenWidth, m_screenHeight;
};
