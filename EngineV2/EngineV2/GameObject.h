#pragma once

#include "Sprite2D.h"


class GameObject{
private:
	WCHAR* textureName;
	int bitmapWidth;
	int bitmapHeight;
	int animationFramesCount;
	Sprite2D* m_Sprite2D;
	D3DXVECTOR2 Position;
	D3DXVECTOR3 Rotation;
	D3DXVECTOR2 Scale;

public:
	GameObject(WCHAR* textureName, int bitmapWidth, int bitmapHeight, float positionX, float positionY, int animationFramesCount);
	bool Initialize(ID3D11Device*, int, int);
	void Shutdown();
	bool Render(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device* device, WCHAR* filename);
	void SetNextAnimationFrame();

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

	void Translate(float posX, float posY);

	void SetModelPosition();
	void SetModelRotation();
	void SetModelScale();

	void Rotate(D3DXVECTOR3 rotation);

	void GetRotationMatrix(D3DXMATRIX &matrix);
};