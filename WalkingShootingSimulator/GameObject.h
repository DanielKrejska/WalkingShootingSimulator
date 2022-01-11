#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class GameObject : public Drawable
{
private:
	virtual void draw(RenderTarget& target, RenderStates states) const;

protected:
	Vector2f position;
	Sprite sprite;

public:
	GameObject(int x = 0, int y = 0);

	void setPosition(int x, int y);
	void setPosition(Vector2f newPosition);

	const Sprite& getSprite();

	Vector2f getPosition();
	Vector2f getCenter();
};
