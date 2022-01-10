#pragma once
#include <SFML/Graphics.hpp>
using sf::Texture;
using std::string;

class TextureHolder
{
public:
	static Texture& getTexture(const string& filename);
};
