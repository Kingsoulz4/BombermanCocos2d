#pragma once

#include "cocos2d.h"
#include "Definition.h"
USING_NS_CC;
class Enemy : public Sprite
{
public:
	Enemy();
	~Enemy();
	virtual void move();

	void setMoveDirection(int direction);
	virtual void enemyDead();
	bool isDead = false;

private:

protected:
	float dtMove = 0.15f;
	float velocity = 10.f;
	int moveDirection;
	

};


