#include "TexturesManager.h"

map<WCHAR*, Texture*> TexturesManager::textures;

bool TexturesManager::GetTexture(ID3D11Device* device, WCHAR* filename, Texture &texture)
{
	//int a = textures.size();
	//ostringstream ss;
	//ss << a;
	//string str = ss.str();
	//OutputDebugStringA(str.c_str());
	
	for (map<WCHAR*, Texture*>::iterator it = textures.begin(); it != textures.end(); it++)
	{
		int check = wcscmp(it->first, filename);
		if (!check)
		{
			texture = *(it->second);
			return true;
		}
	}
	
	textures.insert(pair<WCHAR*, Texture*>(filename, &texture));
	return texture.Initialize(device, filename);
	
}

void TexturesManager::Shutdown()
{
	for (map<WCHAR*, Texture*>::iterator it = textures.begin(); it != textures.end(); it++)
	{
		//delete it->first;
		it->second->Shutdown();
	}
}