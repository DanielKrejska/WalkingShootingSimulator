#include "Bullet.h"

Bullet::Bullet(Vector2f start, Vector2f target)
{
	bulletBody.width = bulletBody.height = 4;
	position = start;
	targetPosition = target;

	shape.setSize(Vector2f(bulletBody.width, bulletBody.height));
	shape.setOutlineThickness(2);
	shape.setOutlineColor(Color::Red);

	bulletBody.left = start.x;
	bulletBody.top = start.y;

	float gradient = (start.x - target.x) / (start.y - target.y);
	gradient = gradient < 0 ? -gradient : gradient;
	
	float ratio = Bullet::SPEED / (1 + gradient);
	frameTravel.x = ratio * gradient;
	frameTravel.y = ratio ;
	
	if (target.x < start.x)
	{
		frameTravel.x *= -1;
	}
	if (target.y < start.y)
	{
		frameTravel.y *= -1;
	}
}

Bullet::~Bullet()
{
}

const FloatRect& Bullet::getRect() const
{
	return bulletBody;
}

const RectangleShape& Bullet::getShape() const
{
	return shape;
}

void Bullet::update(Time dtTime)
{
	position.x += frameTravel.x * dtTime.asSeconds();
	position.y += frameTravel.y * dtTime.asSeconds();

	shape.setPosition(position);
	bulletBody.left = position.x;
	bulletBody.top = position.y;
}
