#pragma once

#include <vector>
#include <cstdlib>
#include <ctime>

//////////////
// MY CLASS INCLUDES //
//////////////
#include "d3dclass.h"
#include "Camera.h"
#include "GameObject.h"
#include "TextureShaderClass.h"
#include "TexturesManager.h"


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

	void SendTranslate(float, float);
	void AddFrameCounter();

private:
	bool Render();
	void BuildLevel();

private:
	int keyPressedFrameCounter;
	D3DClass* m_D3D;
	Camera* m_Camera;
	GameObject* mainGameObject;
	std::vector<GameObject*> gameObjects;
	std::vector<GameObject*> levelObjects;
	TexturesManager* textureManager;
	TextureShaderClass* m_TextureShader;
};
