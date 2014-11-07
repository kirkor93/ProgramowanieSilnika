#pragma once

//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <vector>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "TexturesManager.h"

using namespace std;

class Sprite2D
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:
	Sprite2D(int animationFramesCount);
	Sprite2D(const Sprite2D&);
	~Sprite2D();

	bool Initialize(ID3D11Device*, int, int, WCHAR*, int, int);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, float, float);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

	void SetPosition(D3DXVECTOR2);
	void SetScale(D3DXVECTOR2);
	void SetRotation(D3DXVECTOR3);

	void SetNextAnimationFrame();
	bool LoadTexture(ID3D11Device*, WCHAR*);

	void GetRotationMatrix(D3DXMATRIX &matrix);


private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	bool UpdateBuffers(ID3D11DeviceContext*, float, float);
	void RenderBuffers(ID3D11DeviceContext*);

	
	void ReleaseTexture();

private:

	D3DXVECTOR2 Position;
	D3DXVECTOR3 Rotation;
	D3DXVECTOR2 Scale;

	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount, currentAnimationFrame, animationFramesCount;
	float animationFrameOffset, animationCoord1, animationCoord2;
	vector<Texture*> m_Texture;

	int m_screenWidth, m_screenHeight;
	int m_bitmapWidth, m_bitmapHeight;
	float m_previousPosX, m_previousPosY;
};
