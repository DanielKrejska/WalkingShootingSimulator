#include "Target.h"
#include "TextureHolder.h"
#define TARGET_SCALE Vector2f(0.15f, 0.15f)
#define START_HP 5
Target::Target(Vector2f position)
{
	hp = START_HP;
	this->position = position;
	sprite.setPosition(this->position);
	sprite.setTexture(TextureHolder::getTexture("graphics/target.png"));
	sprite.setScale(TARGET_SCALE);
	auto tempRect = sprite.getGlobalBounds();
	const float weirdConst = tempRect.height / 9;
	collideRect.setPosition(tempRect.left, tempRect.top + weirdConst);
	collideRect.setSize(Vector2f(tempRect.width, tempRect.height - (weirdConst)));
	collideRect.setFillColor(Color::Transparent);
	collideRect.setOutlineThickness(2);
	healthbarBg.setSize(Vector2f(tempRect.width, weirdConst));
	healthbarBg.setPosition(this->position.x, this->position.y - 5 - weirdConst);
	healthbarBg.setFillColor(Color(142, 142, 142));
	currentHealthbar.setPosition(healthbarBg.getPosition());
	currentHealthbar.setSize(healthbarBg.getSize());
	currentHealthbar.setFillColor(Color::Green);
}

Target::~Target()
{
}

void Target::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(sprite, states);
	//target.draw(collideRect, states);
	target.draw(healthbarBg, states);
	target.draw(currentHealthbar, states);
}

bool Target::isDestroyed() const
{
	return hp <= 0;
}

void Target::takeDamage(int damagePoints)
{
	Vector2f newSize(currentHealthbar.getSize().x - (healthbarBg.getSize().x / START_HP),
		currentHealthbar.getSize().y);
	currentHealthbar.setSize(newSize);
	hp -= damagePoints;
}

const FloatRect Target::getColliderRect() const
{
	return collideRect.getGlobalBounds();
}
