#pragma once

//////////////
// INCLUDES //
//////////////
#include <windows.h>

/////////////////
// MY INCLUDES //
/////////////////
#include "D3DClass.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class Graphics
{
public:
	Graphics();
	Graphics(const Graphics&);
	~Graphics();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render();

	D3DClass *m_D3D;
};

