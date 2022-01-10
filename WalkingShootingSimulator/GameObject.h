#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class GameObject
{
protected:
	Vector2f position;
	Sprite sprite;
public:
	GameObject(int x = 0, int y = 0);

	void setPosition(int x, int y);
	void setPosition(Vector2f newPosition);

	const Sprite& getSprite();

	Vector2f getPosition();
};
