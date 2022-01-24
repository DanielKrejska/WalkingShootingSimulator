#include "Bullet.h"

Bullet::Bullet(Vector2f start, Vector2f target)
{
	bulletBody.setPosition(start);
	targetPosition = target;

	float gradient = (start.x - target.x) / (start.y - target.y);
	gradient = gradient > 0 ? gradient : gradient * (-1);
	
	float ratio = Bullet::SPEED / (1 + gradient);
	frameTravel.x = ratio;
	frameTravel.y = ratio * gradient;
	
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

const FloatRect& Bullet::getRect()
{
	return bulletBody.getGlobalBounds();
}

void Bullet::update(Time dtTime)
{
	Vector2f pos = bulletBody.getPosition();
	pos.x += frameTravel.x * dtTime.asSeconds();
	pos.y += frameTravel.y * dtTime.asSeconds();
	bulletBody.setPosition(pos);
}
