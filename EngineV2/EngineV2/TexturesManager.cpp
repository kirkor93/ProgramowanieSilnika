#include "TexturesManager.h"

map<WCHAR*, Texture*> TexturesManager::textures;

bool TexturesManager::GetTexture(ID3D11Device* device, WCHAR* filename, Texture &texture)
{
	///////Exceptions version
	try
	{
		texture = *(textures.at(filename));
	}
	catch (std::out_of_range)
	{
		textures.insert(pair<WCHAR*, Texture*>(filename, &texture));
		return texture.Initialize(device, filename);
	}

	return true;
}

void TexturesManager::Shutdown()
{
	for (map<WCHAR*, Texture*>::iterator it = textures.begin(); it != textures.end(); it++)
	{
		it->second->Shutdown();
	}
}