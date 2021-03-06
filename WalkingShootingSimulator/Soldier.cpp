#pragma warning(disable : 26812)
#pragma warning(disable : 4244)
#pragma warning(disable : 4715)
#include "Soldier.h"
#include "TextureHolder.h"
#include <math.h>
#define SOLDIER_SCALE Vector2f(0.6f, 0.6f)
#define RECT_SCALE 0.48f

#include <iostream>
using namespace std;

Soldier::Soldier() : GameObject(0, 0)
{
	this->reset();
	verticalMove = horizontalMove = 0.f;
	sprite.setTexture(TextureHolder::getTexture
	("graphics/soldier/handgun/idle.png"));
	sprite.setTextureRect(IntRect(0, 0, 5060/20, 216));
	sprite.setScale(SOLDIER_SCALE);
	auto tempRect = sprite.getGlobalBounds();
	rect.setSize(Vector2f(tempRect.width*RECT_SCALE, tempRect.height*RECT_SCALE));
	rect.setOutlineThickness(2);
	rect.setOutlineColor(Color::Yellow);
	rect.setFillColor(Color::Transparent);
	this->sprite.setOrigin(tempRect.width * 0.8, tempRect.height * 0.9);
	anims[HANDGUN][IDLE].setup(20, 5060, 216, seconds(2.2f));
	anims[HANDGUN][MOVE].setup(20, 5160, 220, seconds(.8f));
	anims[HANDGUN][RELOAD].setup(15, 3900, 230, seconds(RELOAD_DURATION));
	anims[HANDGUN][SHOOT].setup(3, 900, 215, seconds(SHOOT_DURATION));
	anims[RIFLE][IDLE].setup(20, 6260, 207, seconds(2.2f));
	anims[RIFLE][MOVE].setup(20, 6260, 206, seconds(.8f));
	anims[RIFLE][RELOAD].setup(20, 6440, 217, seconds(RELOAD_DURATION));
	anims[RIFLE][SHOOT].setup(3, 1020, 206, seconds(SHOOT_DURATION));
}

Soldier::~Soldier()
{
}

void Soldier::reset()
{
	currentState = PlayerState::IDLE;
	canShoot = true;
	equipedWeapon = WeaponTypes::HANDGUN;
	shootTime = reloadingTime = Time::Zero;
	this->animationsReset();
	currHandMag = Soldier::HAND_MAG;
	currRifleMag = Soldier::RIFLE_MAG;
}

void Soldier::animationsReset()
{
	for (int weapon = 0; weapon <= RIFLE; weapon++)
	{
		for (int state = 0; state <= RELOAD; state++)
		{
			anims[weapon][state].reset();
		}
	}
}

void Soldier::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(sprite, states);
	//target.draw(rect, states);
}

Soldier::WeaponTypes Soldier::getWeapon() const
{
	return equipedWeapon;
}

void Soldier::setWeapon(WeaponTypes newWeapon)
{
	if (currentState == PlayerState::SHOOT) return;
	equipedWeapon = newWeapon;
	canShoot = true;
	currentState = PlayerState::IDLE;
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

Vector2f Soldier::getCenter() const
{
	auto rp = rect.getGlobalBounds();
	return Vector2f(rp.left + (rp.width / 2),
		rp.top + (rp.height / 2));
}

void Soldier::setSpritePosition()
{
	sprite.setPosition(this->getCenter());
}

void Soldier::setRectPosition()
{
	rect.setPosition(position);
}

void Soldier::rotate(float angle)
{
	sprite.setRotation(angle);
}

bool Soldier::isWalking() const
{
	bool isWalking = horizontalMove != 0.f || verticalMove != 0.f;
	return isWalking;
}

int Soldier::getState()
{
	return currentState;
}

bool Soldier::shootAvailable()
{
	return canShoot;
}

int Soldier::checkMag()
{
	switch (equipedWeapon)
	{
	case WeaponTypes::HANDGUN:
		return currHandMag;
		break;
	case WeaponTypes::RIFLE:
		return currRifleMag;
		break;
	}
}

bool Soldier::shoot()
{
	if (!this->checkMag()) return false;
	currentState = PlayerState::SHOOT;
	shootTime = Time::Zero;
	this->animationsReset();
	canShoot = false;
	return true;
}

void Soldier::reload()
{
	currentState = PlayerState::RELOAD;
	this->animationsReset();
	reloadingTime = Time::Zero;
}

void Soldier::reloadMag()
{
	if (equipedWeapon == WeaponTypes::HANDGUN)
		currHandMag = Soldier::HAND_MAG;
	else
		currRifleMag = Soldier::RIFLE_MAG;
}

void Soldier::animationUpdate(Time dtTime)
{
	switch (currentState)
	{
	case PlayerState::IDLE:
		if (equipedWeapon == HANDGUN)
			sprite.setTexture(TextureHolder::getTexture("graphics/soldier/handgun/idle.png"));
		else if (equipedWeapon == RIFLE)
			sprite.setTexture(TextureHolder::getTexture("graphics/soldier/rifle/idle.png"));
		break;
	case PlayerState::MOVE:
		if (equipedWeapon == HANDGUN)
			sprite.setTexture(TextureHolder::getTexture("graphics/soldier/handgun/move.png"));
		else if (equipedWeapon == RIFLE)
			sprite.setTexture(TextureHolder::getTexture("graphics/soldier/rifle/move.png"));
		break;
	case PlayerState::RELOAD:
		if (equipedWeapon == HANDGUN)
			sprite.setTexture(TextureHolder::getTexture("graphics/soldier/handgun/reload.png"));
		else if (equipedWeapon == RIFLE)
			sprite.setTexture(TextureHolder::getTexture("graphics/soldier/rifle/reload.png"));
		break;
	case PlayerState::SHOOT:
		if (equipedWeapon == HANDGUN)
			sprite.setTexture(TextureHolder::getTexture("graphics/soldier/handgun/shoot.png"));
		else if (equipedWeapon == RIFLE)
			sprite.setTexture(TextureHolder::getTexture("graphics/soldier/rifle/shoot.png"));
		break;
	}
	sprite.setTextureRect(anims[equipedWeapon][currentState].update(dtTime));
}

void Soldier::stateUpdate(Time dtTime)
{
	// ukon?en? v?st?elu a p?eb?jen?
	if (reloadingTime.asSeconds() >= RELOAD_DURATION &&
		currentState == PlayerState::RELOAD)
	{
		currentState = PlayerState::IDLE;
		canShoot = true;
		this->animationsReset();
		this->reloadMag();
	}
	else if (shootTime.asSeconds() >= SHOOT_DURATION &&
		currentState == PlayerState::SHOOT)
	{
		currentState = PlayerState::IDLE;
		canShoot = true;
		this->animationsReset();
		if (equipedWeapon == WeaponTypes::HANDGUN)
			currHandMag--;
		else 
			currRifleMag--;
	}

	// nastaven? statusu
	if (currentState != RELOAD && currentState != SHOOT)
	{
		if (oldPosition != position)
		{
			currentState = PlayerState::MOVE;
		}
		else
		{
			currentState = PlayerState::IDLE;
		}
	}

	// reakce na stav
	if (currentState == PlayerState::RELOAD)
	{
		reloadingTime += dtTime;
	}
	else if (currentState == PlayerState::SHOOT)
	{
		shootTime += dtTime;
	}
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
	this->setRectPosition();
	this->setSpritePosition();
}
