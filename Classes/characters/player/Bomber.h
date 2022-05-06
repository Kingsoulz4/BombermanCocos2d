#pragma once

#include "cocos2d.h"
#include <math.h>
#include "Definition.h"
USING_NS_CC;

class Bomber : public Sprite
{
public:

	static Bomber* create(const std::string& file);
	void setVelocity(float velocity);
	float getVelocity();
	void move();
	void move(float cosA, float sinA);
	void walkSouth();
	void walkNorth();
	void walkEast();
	void walkWest();
	int getMoveDirection();
	void useWeapon();

private:
	float velocity = 10.f;
	float dtMove = 0.15f;
	int nMovePerUnit = 5;
	int moveDirection; 
	int currentWeapon;
};

