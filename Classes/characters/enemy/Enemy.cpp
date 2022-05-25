#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::move()
{
	if (!isMoving || isDead)
	{
		return;
	}
	dtMove = 0.15f;
	velocity = 5.f;
	if (moveDirection == MOVE_NORTH)
	{
		moveNorth();
	}
	else if (moveDirection == MOVE_EAST)
	{
		moveEast();
	}
	else if (moveDirection == MOVE_WEST)
	{
		moveWest();
	}
	else if (moveDirection == MOVE_SOUTH)
	{
		moveSouth();
	}
}

void Enemy::moveNorth()
{
}

void Enemy::moveEast()
{
}

void Enemy::moveWest()
{
}

void Enemy::moveSouth()
{
}

void Enemy::setMoveDirection(int direction)
{
	moveDirection = direction;
}

int Enemy::getMoveDirection()
{
	return this->moveDirection;
}

float Enemy::getVelocity()
{
	return this->velocity;
}

void Enemy::changeDirection()
{
}

void Enemy::enemyDead()
{
	isDead = true;
	
}

void Enemy::update(float dt)
{
	
	/*this->scheduleOnce(schedule_selector(LowGian::move), 1.5f));
	this->changeDirection();*/
	float offset = velocity * 3 * battleScene->tileMapScaled;
	if (moveStatus == MOVE_VIA_AILOW)
	{
		this->move();
		if (moveDirection == MOVE_EAST && battleScene->detectCollision(Point(this->getPositionX() + offset, this->getPositionY())))
		{
			changeDirection();
		}
		else if (moveDirection == MOVE_WEST && battleScene->detectCollision(Point(this->getPositionX() - offset, this->getPositionY())))
		{
			changeDirection();
		}
		else if (moveDirection == MOVE_NORTH && battleScene->detectCollision(Point(this->getPositionX(), this->getPositionY() + offset)))
		{
			changeDirection();
		}
		else if (moveDirection == MOVE_SOUTH && battleScene->detectCollision(Point(this->getPositionX(), this->getPositionY() - offset)))
		{
			changeDirection();
		}
		else
		{
			isMoving = true;
		}
		//Update Time to change direction
		//CCLOG("time To change direction: %f", timeToChangeDirection);
		if (timeToChangeDirection > 0)
		{
			timeToChangeDirection -= dt;
		}
		if (timeToChangeDirection <= 0)
		{
			timeToChangeDirection = randRange(1, 5);
			changeDirection();
		}
	}
	
}

Enemy* Enemy::create(BattleScene* battleScene)
{
	auto ret = new (std::nothrow) Enemy;
	if (ret && ret->init()) {
		ret->autorelease();
		ret->battleScene = battleScene;
		return ret;
	}
	CC_SAFE_RELEASE(ret);
	
	return nullptr;
}
