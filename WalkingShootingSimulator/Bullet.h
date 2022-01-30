#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Bullet
{
private:
	static const int SPEED = 3800;

	FloatRect bulletBody;
	RectangleShape shape;

	Vector2f position;

	// horizontální a vertikální vzdálenost, kterou musí
	// kulka cestovat každý frame
	Vector2f frameTravel;

	Vector2f targetPosition;

public:
	Bullet(Vector2f start, Vector2f target);
	~Bullet();

	void update(Time dtTime);

	const FloatRect& getRect() const;
	const RectangleShape& getShape() const;
};
