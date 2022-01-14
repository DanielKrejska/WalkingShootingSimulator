#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#define SLANT_MOVE_KOEF 0.70710678f
using namespace sf;

class Soldier : public GameObject
{
private:
	enum PlayerState {
		IDLE = 0,
		MOVE,
		SHOOT,
		RELOAD
	};

	enum WeaponTypes {
		HANDGUN = 0,
		SHOTGUN,
		RIFLE
	};

	virtual void draw(RenderTarget& target, RenderStates states) const;

	PlayerState currentState;
	WeaponTypes equipedWeapon;
	RectangleShape rect;
	Sprite sprite;

	float verticalMove;
	float horizontalMove;
	Vector2f oldPosition;

public:
	static const int MOVE_SPEED = 135;

	void setPosition(float x, float y);
	void setPosition(Vector2f newPosition);

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	// vrací pozici na nadcházejícím framu
	Vector2f calculateNextPosition(Time dtTime);
	// vrací pozici na pøedchozím framu
	Vector2f getOldPosition();
	void executeMovement(Vector2f nextPosition);

	void setVertical(float value);
	void setHorizontal(float value);
	float getVertical();
	float getHorizontal();
	const RectangleShape& getRect() const;
	Vector2f getCenter() const;

	Soldier();
	~Soldier();
};
