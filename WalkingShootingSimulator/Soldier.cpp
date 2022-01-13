#pragma warning(disable : 26812)
#include "Soldier.h"
#include "TextureHolder.h"
#define SOLDIER_SCALE Vector2f(0.6f, 0.6f)


Soldier::Soldier() : GameObject(0, 0)
{
	currentState = PlayerState::IDLE;
	equipedWeapon = WeaponTypes::HANDGUN;
	verticalMove = horizontalMove = 0.f;
	sprite.setTexture(TextureHolder::getTexture
	("graphics/soldier/handgun/idle.png"));
	sprite.setTextureRect(IntRect(0, 0, 5060/20, 216));
	sprite.setScale(SOLDIER_SCALE);
	auto tempRect = sprite.getGlobalBounds();
	rect.setSize(Vector2f(tempRect.width, tempRect.height));
	rect.setOutlineThickness(2);
	rect.setOutlineColor(Color::Yellow);
	rect.setFillColor(Color::Transparent);
}

Soldier::~Soldier()
{
}

void Soldier::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(sprite, states);
	target.draw(rect, states);
}

void Soldier::setPosition(float x, float y)
{
	position = Vector2f(x, y);
	oldPosition = position;
}

void Soldier::setPosition(Vector2f newPosition)
{
	position = newPosition;
	oldPosition = position;
}

const RectangleShape& Soldier::getRect() const
{
	return rect;
}

float Soldier::getVertical()
{
	return verticalMove;
}

float Soldier::getHorizontal()
{
	return horizontalMove;
}

void Soldier::setVertical(float value)
{
	verticalMove = value;
}

void Soldier::setHorizontal(float value)
{
	horizontalMove = value;
}

Vector2f Soldier::getOldPosition()
{
	return oldPosition;
}

/*
* POHYB
*/

void Soldier::moveUp()
{
	verticalMove -= 1;
}

void Soldier::moveDown()
{
	verticalMove += 1;
}

void Soldier::moveLeft()
{
	horizontalMove -= 1;
}

void Soldier::moveRight()
{
	horizontalMove += 1;
}

Vector2f Soldier::calculateNextPosition(Time dtTime)
{
	Vector2f nextPos;
	if (horizontalMove != 0 && verticalMove != 0)
	{
		float actualSpeed = MOVE_SPEED * SLANT_MOVE_KOEF * dtTime.asSeconds();
		nextPos.x = position.x + (actualSpeed * horizontalMove);
		nextPos.y = position.y + (actualSpeed * verticalMove);
	}
	else
	{
		nextPos.x = position.x + (MOVE_SPEED * dtTime.asSeconds() * horizontalMove);
		nextPos.y = position.y + (MOVE_SPEED * dtTime.asSeconds() * verticalMove);
	}
	return nextPos;
}

void Soldier::executeMovement(Vector2f nextPosition)
{
	oldPosition = position;
	position = nextPosition;
	horizontalMove = verticalMove = 0;
	sprite.setPosition(position);
	auto tempRect = sprite.getGlobalBounds();
	rect.setPosition(tempRect.left, tempRect.top);
}
