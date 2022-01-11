#pragma warning(disable : 26812)
#include "Soldier.h"
#include "TextureHolder.h"
#define SOLDIER_SCALE Vector2f(0.65f, 0.65f)

#include <iostream>
using namespace std;

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
	rect.setOutlineThickness(5);
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
	cout << position.x << "    " << position.y << endl;
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

void Soldier::executeMovement(Time dtTime)
{
	if (horizontalMove != 0 && verticalMove != 0)
	{
		float actualSpeed = MOVE_SPEED * SLANT_MOVE_KOEF * dtTime.asSeconds();
		position.x += actualSpeed * verticalMove;
		position.y += actualSpeed * horizontalMove;
	}
	else
	{
		position.x += MOVE_SPEED * dtTime.asSeconds() * horizontalMove;
		position.y += MOVE_SPEED * dtTime.asSeconds() * verticalMove;
	}
	horizontalMove = verticalMove = 0;
	sprite.setPosition(position);
	auto tempRect = sprite.getGlobalBounds();
	rect.setPosition(tempRect.left, tempRect.top);
}
