#pragma warning(disable : 26812)
#include "Soldier.h"
#include "TextureHolder.h"


Soldier::Soldier() : GameObject(0, 0)
{
	currentState = PlayerState::IDLE;
	equipedWeapon = WeaponTypes::HANDGUN;
}

Soldier::~Soldier()
{
}
