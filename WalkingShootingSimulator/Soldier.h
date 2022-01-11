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

public:
	static const int MOVE_SPEED = 5;

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void executeMovement(Time dtTime);

	Soldier();
	~Soldier();
};
