#pragma once

#include "cocos2d.h"
#include "Definition.h"
#include "BattleScene.h"
#include "ai/AI.h"

USING_NS_CC;
class Enemy : public Sprite
{
public:
	Enemy();
	~Enemy();
	virtual void move();
	virtual void moveNorth();
	virtual void moveEast();
	virtual void moveWest();
	virtual void moveSouth();


	void setMoveDirection(int direction);
	int getMoveDirection();
	float getVelocity();
	virtual void changeDirection();
	virtual void enemyDead();
	bool isDead = false;
	bool isMoving = true;
	void update(float dt);
	BattleScene* battleScene;
	static Enemy* create(BattleScene* battleScene);
	float deadTime = 2;
	float timeToChangeDirection = 5.f;
	AI* ai;

private:

protected:
	int moveStatus = MOVE_VIA_AILOW; 
	float dtMove = 1.5f;
	float velocity = 10.f;
	int moveDirection = MOVE_EAST;
	

};


