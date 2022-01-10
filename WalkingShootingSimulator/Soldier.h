#pragma once
#include "GameObject.h"

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


	PlayerState currentState;
	WeaponTypes equipedWeapon;
	RectangleShape rect;
	Sprite sprite;

public:

	Soldier();
	~Soldier();
};
