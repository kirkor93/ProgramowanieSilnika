#pragma once

#include <map>
#include <string>

#include "Texture.h"

using namespace std;

class TexturesManager
{
public:
	static bool LoadTexture(ID3D11Device* device, WCHAR* filename);


private:
	static map<WCHAR*, Texture*> textures;
};

