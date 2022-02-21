#pragma once
#include "GameObject.h"

class Target : public GameObject
{
private:
	int hp;
	RectangleShape collideRect;
	RectangleShape currentHealthbar;
	RectangleShape healthbarBg;
	virtual void draw(RenderTarget& target, RenderStates states) const;

public:
	Target(Vector2f position);
	bool isDestroyed() const;
	void takeDamage(int damagePoints);
	const FloatRect getColliderRect() const;
	~Target();
};
