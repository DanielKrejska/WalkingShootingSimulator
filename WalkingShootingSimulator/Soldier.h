#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameObject.h"
#include "Animation.h"
#define SLANT_MOVE_KOEF 0.70710678f
#define SHOOT_DURATION 0.15f
#define RELOAD_DURATION 2.f
using namespace sf;

class Soldier : public GameObject
{
public:
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

private:
	Time reloadingTime;
	Time shootTime;

	bool canShoot;

	int currHandMag;
	int currRifleMag;
	int currShotMag;

	virtual void draw(RenderTarget& target, RenderStates states) const;

	PlayerState currentState;
	WeaponTypes equipedWeapon;
	RectangleShape rect;
	Sprite sprite;

	Animation anims[RIFLE+1][RELOAD+1];

	float verticalMove;
	float horizontalMove;
	Vector2f oldPosition;

	void setSpritePosition();
	void setRectPosition();

	void reloadMag();

public:
	static const int MOVE_SPEED = 135;
	static const int HAND_MAG = 10;
	static const int RIFLE_MAG = 30;
	static const int SHOT_MAG = 6;

	void reset();
	void animationsReset();

	void setPosition(float x, float y);
	void setPosition(Vector2f newPosition);

	void reload();
	bool shoot();

	void rotate(float angle);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	// vrací pozici na nadcházejícím framu
	Vector2f calculateNextPosition(Time dtTime);
	// vrací pozici na pøedchozím framu
	Vector2f getOldPosition();
	void executeMovement(Vector2f nextPosition);

	void animationUpdate(Time dtTime);
	void stateUpdate(Time dtTime);

	void setWeapon(WeaponTypes newWeapon);
	Soldier::WeaponTypes getWeapon() const;
	void setVertical(float value);
	void setHorizontal(float value);
	float getVertical();
	float getHorizontal();
	const RectangleShape& getRect() const;
	Vector2f getCenter();
	int getState();
	bool shootAvailable();
	int checkMag();

	Soldier();
	~Soldier();
};
