#pragma once

#include "Sprite2D.h"


class GameObject{
private:
	WCHAR* textureName;
	int bitmapWidth;
	int bitmapHeight;
	Sprite2D* m_Sprite2D;
	D3DXVECTOR2 Position;
	D3DXVECTOR2 Rotation;
	D3DXVECTOR2 Scale;

public:
	GameObject(WCHAR* textureName, int bitmapWidth, int bitmapHeight, float positionX, float positionY);
	bool Initialize(ID3D11Device*, int, int);
	void Shutdown();
	bool Render(ID3D11DeviceContext*);
	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

	void Translate(float posX, float posY);

	void SetModelPosition();
	void SetModelRotation();
	void SetModelScale();

};