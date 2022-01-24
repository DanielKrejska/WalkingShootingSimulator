#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Bullet
{
private:
	static const int SPEED = 500;

	RectangleShape bulletBody;

	// horizont�ln� a vertik�ln� vzd�lenost, kterou mus�
	// kulka cestovat ka�d� frame
	Vector2f frameTravel;

	Vector2f targetPosition;

public:
	Bullet(Vector2f start, Vector2f target);
	~Bullet();

	void update(Time dtTime);

	const FloatRect& getRect();
};

