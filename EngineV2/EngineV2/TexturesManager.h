#pragma once

#include <map>
#include <string>
#include <sstream>

#include "Texture.h"
#include "Converter.h"

using namespace std;

class TexturesManager
{
public:
	static bool GetTexture(ID3D11Device* device, WCHAR* filename, Texture &texture);
	static void Shutdown();

private:
	static map<WCHAR*, Texture*> textures;
};