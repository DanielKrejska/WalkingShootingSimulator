#include "TextureHolder.h"
using std::map;

Texture& TextureHolder::getTexture(const string& filename)
{
	static map<string, Texture> textureStorage;

	auto pair = textureStorage.find(filename);
	
	if (pair != textureStorage.end())
	{
		return pair->second;
	}
	else
	{
		auto& newTexture = textureStorage[filename];
		newTexture.loadFromFile(filename);
		return newTexture;
	}
}
