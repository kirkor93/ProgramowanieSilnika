#include "TexturesManager.h"


TexturesManager::TexturesManager()
{
}


TexturesManager::~TexturesManager()
{
}

bool TexturesManager::GetTexture(ID3D11Device* device, WCHAR* filename, Texture *texture)
{
	int size = textures.size();
	texture = textures[filename];
	if (size < textures.size())
	{
		texture = new Texture;
		texture->Initialize(device, filename);
		return true;
	}

	return true;
}

void TexturesManager::Shutdown()
{
	for (map<WCHAR*, Texture*>::iterator it = textures.begin(); it != textures.end(); it++)
	{
		delete it->first;
		it->second->Shutdown();
	}
}