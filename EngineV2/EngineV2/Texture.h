#pragma once

//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx11tex.h>
#include <vector>

class Texture
{
public:
	Texture();
	Texture(const Texture&);
	~Texture();

	
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();
	bool Initialize(ID3D11Device*, WCHAR*);


private:
	ID3D11ShaderResourceView* m_texture;

};
