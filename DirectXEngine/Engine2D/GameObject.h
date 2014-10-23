#pragma once

// includes
#include <d3d11.h>
#include <d3dx10math.h>
#include <vector>
//my classes
#include "System.h"
#include "Model.h"
#include "Sprite2D.h"
#include "Texture.h"
#include "TextureShader.h"
//using namespace std;

class GameObject
{
protected:
	string myName;
	string myTag;

	Model* myModel;
	Texture* myTexture;
	TextureShader* myShader;

	unsigned int animationLastFrame;
	unsigned int currentTextureID;
	vector<Texture*> animationTextures;
	bool canAnimate;

	virtual bool InitializeModel(ID3D11Device* device, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale);
	virtual void AnimateTexture();
public:
	GameObject();
	GameObject(string name, string tag, Texture* texture, TextureShader* shader, ID3D11Device*, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale);
	GameObject(string name, string tag, Texture* animationTextures[], unsigned int textureCount, TextureShader* shader, ID3D11Device*, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale);
	GameObject(const GameObject&);
	~GameObject();

	bool Render(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix);
	void Destroy();

	string GetName();
	string GetTag();

	void SetPosition(D3DXVECTOR3);
	void SetRotation(D3DXVECTOR3);
	void SetScale(D3DXVECTOR3);
	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();
	D3DXVECTOR3 GetScale();
};

