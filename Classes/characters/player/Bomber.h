#pragma once

#include "cocos2d.h"
#include <math.h>
#include "Definition.h"
#include "weapons/Bomb.h"
#include "audio/AudioManager.h"


USING_NS_CC;
//class BattleScene;

class Bomber : public Sprite
{
public:
	//BattleScene* battleScene;

	static Bomber* create();
	void setVelocity(float velocity);
	float getVelocity();
	void move();
	void move(float cosA, float sinA);
	void walkSouth();
	void walkNorth();
	void walkEast();
	void walkWest();
	void dead();
	int getMoveDirection();
	void setMoveDirection(int dir);
	void useWeapon();
	void useItem(int type);
	void increaseBombLimit();
	int getBombLimit();
	std::vector<Bomb*> bombPlaced;
	void increaseVelocity();
	void increaseLife();
	int getLife();
	int getFlamePower();
	void increaseFlamePower();
	float deadTime = 2;
	bool _canMove = true;
	

	


private:
	float velocity = 10.f;
	float dtMove = 0.15f;
	int nMovePerUnit = 5;
	int moveDirection; 
	int currentWeapon;
	int bombLimit = 1;
	int life = 3;
	int flamePower = 1;
};

