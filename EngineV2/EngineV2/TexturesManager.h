#pragma once

#include <map>

#include "Texture.h"

using namespace std;

class TexturesManager
{
public:
	TexturesManager();
	~TexturesManager();

	bool GetTexture(ID3D11Device* device, WCHAR* filename, Texture *texture);
	void Shutdown();

private:
	map<WCHAR*, Texture*> textures;
};

