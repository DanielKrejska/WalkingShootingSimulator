#pragma warning(disable : 4244)
#include "GameObject.h"

GameObject::GameObject(int x, int y)
{
	this->setPosition(x, y);
}

void GameObject::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(sprite, states);
}

void GameObject::setPosition(int x, int y)
{
	position = Vector2f(x, y);
}

void GameObject::setPosition(Vector2f newPosition)
{
	position = newPosition;
}

Vector2f GameObject::getPosition()
{
	return position;
}

Vector2f GameObject::getCenter()
{
}

const Sprite& GameObject::getSprite()
{
	return sprite;
}
