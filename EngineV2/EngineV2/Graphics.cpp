#include "Graphics.h"


Graphics::Graphics()
{
	m_D3D = 0;
	m_Camera = 0;
	mainGameObject = 0;
	m_TextureShader = 0;
	keyPressedFrameCounter = 0;
}


Graphics::Graphics(const Graphics& other)
{
}


Graphics::~Graphics()
{
}


bool Graphics::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	srand(time(NULL));
	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new Camera;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	///////////////////////////////////////////////////////////////////////////////////////////
	// Create the MAIN game object.
	mainGameObject = new GameObject(L"./Textures/Main_champ_1.dds", 128, 128, 320, 240);
	if (!mainGameObject)
	{
		return false;
	}

	// Initialize the model object.
	result = mainGameObject->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	mainGameObject->LoadTexture(m_D3D->GetDevice(), L"./Textures/Main_champ_2.dds");
	mainGameObject->LoadTexture(m_D3D->GetDevice(), L"./Textures/Main_champ_3.dds");
	mainGameObject->LoadTexture(m_D3D->GetDevice(), L"./Textures/Main_champ_4.dds");
	mainGameObject->LoadTexture(m_D3D->GetDevice(), L"./Textures/Main_champ_5.dds");
	mainGameObject->LoadTexture(m_D3D->GetDevice(), L"./Textures/Main_champ_6.dds");
	mainGameObject->LoadTexture(m_D3D->GetDevice(), L"./Textures/Main_champ_7.dds");
	mainGameObject->LoadTexture(m_D3D->GetDevice(), L"./Textures/Main_champ_8.dds");

	////////////////////////////////////////////////////////////////////////////////////////////

	// Create other game objects.
	BuildLevel();
	gameObjects.push_back(new GameObject(L"./Textures/Alien.dds", 128, 128, 100, 100));



	// Initialize other game objects.

	for (int i = 0; i < gameObjects.size(); i += 1)
	{
		result = gameObjects[i]->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the gameobject.", L"Error", MB_OK);
			return false;
		}
	}

	for (int i = 0; i < levelObjects.size(); i += 1)
	{
		result = levelObjects[i]->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize level object.", L"Error", MB_OK);
			return false;
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////


	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void Graphics::Shutdown()
{

	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the model object.
	if (mainGameObject)
	{
		mainGameObject->Shutdown();
		delete mainGameObject;
		mainGameObject = 0;
	}

	if (gameObjects.size()>0)
	{
		for (int i = 0; i < gameObjects.size(); i += 1)
		{
			gameObjects[i]->Shutdown();
		}
		gameObjects.clear();
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	//Release the D3D object
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool Graphics::Frame()
{
	bool result;

	// Render the graphics scene.
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}


bool Graphics::Render()
{
	D3DXMATRIX viewMatrix, orthoMatrix, worldMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	if (levelObjects.size()>0)
	{
		for (int i = 0; i < levelObjects.size(); i += 1)
		{
			result = levelObjects[i]->Render(m_D3D->GetDeviceContext());
			if (!result)
			{
				return false;
			}
			result = m_TextureShader->Render(m_D3D->GetDeviceContext(), levelObjects[i]->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, levelObjects[i]->GetTexture());
			if (!result)
			{
				return false;
			}
		}
	}

	if (gameObjects.size()>0)
	{
		for (int i = 0; i < gameObjects.size(); i += 1)
		{
			result = gameObjects[i]->Render(m_D3D->GetDeviceContext());
			if (!result)
			{
				return false;
			}
			result = m_TextureShader->Render(m_D3D->GetDeviceContext(), gameObjects[i]->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, gameObjects[i]->GetTexture());
			if (!result)
			{
				return false;
			}
		}
	}

	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = mainGameObject->Render(m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Render the bitmap with the texture shader.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), mainGameObject->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, mainGameObject->GetTexture());
	if (!result)
	{
		return false;
	}

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

void Graphics::SendTranslate(float positionX, float positionY)
{
	this->mainGameObject->Translate(positionX, positionY);
	this->m_Camera->Translate(positionX, -positionY, 0.0f);
}

void Graphics::AddFrameCounter()
{
	keyPressedFrameCounter += 1;
	keyPressedFrameCounter %= 1000;

	if (keyPressedFrameCounter % 10 == 0)
	{
		mainGameObject->SetNextAnimationFrame();
		keyPressedFrameCounter++;
	}
}

void Graphics::BuildLevel()
{
	for (int i = -1024; i < 1024; i += 128)
	{
		for (int j = -1024; j < 1024; j += 128)
		{
			int random = rand() % 3;
			switch (random)
			{
			case 0:
				levelObjects.push_back(new GameObject(L"./Textures/Water.dds", 128, 128, i, j));
				break;
			case 1:
				levelObjects.push_back(new GameObject(L"./Textures/Grass.dds", 128, 128, i, j));
				break;
			case 2:
				levelObjects.push_back(new GameObject(L"./Textures/Wall.dds", 128, 128, i, j));
				break;
			default:
				break;
			}
		}
	}
}