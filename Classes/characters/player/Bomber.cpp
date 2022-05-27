#include "Bomber.h"

Bomber * Bomber::create()
{
	auto ret = new (std::nothrow) Bomber;
	if (ret && ret->initWithFile("Sprites/Player/BomberWalkDown1.png")) {
		ret->autorelease();
		//ret->velocity = 1.f; //declare here or in init
		return ret;
	}
	CC_SAFE_RELEASE(ret);
	return nullptr;
}

void Bomber::setVelocity(float velocity)
{
	this->velocity = velocity;
}

float Bomber::getVelocity()
{
	return this->velocity;
}

void Bomber::move()
{
}

void Bomber::move(float cosA, float sinA)
{
	if (!this->_canMove)
	{
		return;
	}
	if (cosA >= sqrt(2)/2 && cosA<=1)
	{
		
		walkEast();
	}
	else if (cosA <= sqrt(2) / 2 && cosA >= -sqrt(2) / 2)
	{
		if (sinA>0)
		{
			walkNorth();
		}
		else if (sinA<0)
		{
			walkSouth();
		}
		
	}
	else if (cosA <= -sqrt(2) / 2 && cosA >= -1)
	{
		walkWest();
	}
	
}

void Bomber::walkSouth()
{
	//this->stopAllActions();
	moveDirection = MOVE_SOUTH;
	auto walkSouthAnimation = Animation::create();
	walkSouthAnimation->setDelayPerUnit(dtMove);
	walkSouthAnimation->setLoops(1);
	walkSouthAnimation->addSpriteFrame(Sprite::create("Sprites/Player/BomberWalkDown1.png")->getSpriteFrame());
	walkSouthAnimation->addSpriteFrame(Sprite::create("Sprites/Player/BomberWalkDown2.png")->getSpriteFrame());
	walkSouthAnimation->addSpriteFrame(Sprite::create("Sprites/Player/BomberWalkDown3.png")->getSpriteFrame());
	walkSouthAnimation->addSpriteFrame(Sprite::create("Sprites/Player/BomberWalkDown4.png")->getSpriteFrame());
	auto walkSouthAnimate = Animate::create(walkSouthAnimation);
	auto bomberWalkSouth = MoveBy::create(dtMove, Vec2(0, -velocity));
	bomberWalkSouth->setTag(21);
	walkSouthAnimate->setTag(11);
	if (this->getActionByTag(11) == nullptr)
	{
		this->runAction(walkSouthAnimate);
	}
	if (this->getActionByTag(21) == nullptr)
	{
		this->runAction(bomberWalkSouth);
	}
	
	
}

void Bomber::walkNorth()
{
	moveDirection = MOVE_NORTH;
	//this->stopAllActions();
	auto walkNorthAnimation = Animation::create();
	walkNorthAnimation->setDelayPerUnit(dtMove);
	walkNorthAnimation->setLoops(1);
	walkNorthAnimation->addSpriteFrame(Sprite::create("Sprites/Player/BomberWalkNorth1.png")->getSpriteFrame());
	walkNorthAnimation->addSpriteFrame(Sprite::create("Sprites/Player/BomberWalkNorth2.png")->getSpriteFrame());
	walkNorthAnimation->addSpriteFrame(Sprite::create("Sprites/Player/BomberWalkNorth3.png")->getSpriteFrame());
	walkNorthAnimation->addSpriteFrame(Sprite::create("Sprites/Player/BomberWalkNorth4.png")->getSpriteFrame());
	auto walkNorthAnimate = Animate::create(walkNorthAnimation);
	auto bomberWalkNorth = MoveBy::create(dtMove, Vec2(0, velocity ));
	bomberWalkNorth->setTag(22);
	walkNorthAnimate->setTag(12);
	if (this->getActionByTag(12) == nullptr)
	{
		this->runAction(walkNorthAnimate);
	}
	if (this->getActionByTag(22) == nullptr)
	{
		this->runAction(bomberWalkNorth);
	}

	
}

void Bomber::walkEast()
{

	moveDirection = MOVE_EAST;
	//this->stopAllActions();
	auto walkEastAnimation = Animation::create();
	walkEastAnimation->setDelayPerUnit(dtMove);
	walkEastAnimation->setLoops(1);
	walkEastAnimation->addSpriteFrame(Sprite::create("Sprites/Player/BomberWalkEast1.png")->getSpriteFrame());
	walkEastAnimation->addSpriteFrame(Sprite::create("Sprites/Player/BomberWalkEast2.png")->getSpriteFrame());
	walkEastAnimation->addSpriteFrame(Sprite::create("Sprites/Player/BomberWalkEast3.png")->getSpriteFrame());
	
	auto walkEastAnimate = Animate::create(walkEastAnimation);
	
	auto bomberWalkEast = MoveBy::create(dtMove, Vec2(velocity, 0));
	bomberWalkEast->setTag(23);
	walkEastAnimate->setTag(13);
	if (this->getActionByTag(13) == nullptr)
	{
		this->runAction(walkEastAnimate);
	}
	if (this->getActionByTag(23) == nullptr)
	{
		this->runAction(bomberWalkEast);
	}
	
	
}

void Bomber::walkWest()
{

	//this->stopAllActions();
	moveDirection = MOVE_WEST;
	auto walkWestAnimation = Animation::create();
	walkWestAnimation->setDelayPerUnit(dtMove);
	walkWestAnimation->setLoops(1);
	walkWestAnimation->addSpriteFrame(Sprite::create("Sprites/Player/BomberWalkWest1.png")->getSpriteFrame());
	walkWestAnimation->addSpriteFrame(Sprite::create("Sprites/Player/BomberWalkWest2.png")->getSpriteFrame());
	walkWestAnimation->addSpriteFrame(Sprite::create("Sprites/Player/BomberWalkWest3.png")->getSpriteFrame());

	auto walkWestAnimate = Animate::create(walkWestAnimation);
	auto bomberWalkWest = MoveBy::create(dtMove, Vec2(-velocity, 0));
	auto walkWestSequence = Sequence::create(walkWestAnimate, bomberWalkWest, NULL);


	bomberWalkWest->setTag(24);
	walkWestAnimate->setTag(14);
	if (this->getActionByTag(14) == nullptr)
	{
		this->runAction(walkWestAnimate);
	}
	if (this->getActionByTag(24) == nullptr)
	{
		this->runAction(bomberWalkWest);
		//moveDirection = 0;
	}
}

void Bomber::dead()
{
	_isDead = true;
	this->stopAllActions();
	auto playerDeadAnimation = Animation::create();
	playerDeadAnimation->setDelayPerUnit(deadTime / 5);
	playerDeadAnimation->setLoops(1);
	playerDeadAnimation->addSpriteFrame(Sprite::create("Sprites/Player/bomberDie1.png")->getSpriteFrame());
	playerDeadAnimation->addSpriteFrame(Sprite::create("Sprites/Player/bomberDie2.png")->getSpriteFrame());
	playerDeadAnimation->addSpriteFrame(Sprite::create("Sprites/Player/bomberDie3.png")->getSpriteFrame());
	playerDeadAnimation->addSpriteFrame(Sprite::create("Sprites/Player/bomberDie4.png")->getSpriteFrame());
	playerDeadAnimation->addSpriteFrame(Sprite::create("Sprites/Player/bomberDie5.png")->getSpriteFrame());
	auto playerDeadAnimate = Animate::create(playerDeadAnimation);
	this->runAction(playerDeadAnimate);



}

int Bomber::getMoveDirection()
{
	return this->moveDirection;
}

void Bomber::setMoveDirection(int dir)
{
	this->moveDirection = dir;
}

void Bomber::useWeapon()
{
	AudioManger::getInstance()->playBomberPlaceBomb();
}

void Bomber::useItem(int type)
{
	CCLOG("use item %i", type);

	if (type == BONUS_BOMB_ITEM)
	{
		increaseBombLimit();
	}
	if (type == SPEEDUP_ITEM)
	{
		increaseVelocity();
	}
	if (type == SPEEDUP_ITEM)
	{

	}
	if (type == BONUS_LIFE_ITEM)
	{
		increaseLife();
	}
	if (type == POWERUP_FLAME_BOMB)
	{
		increaseFlamePower();
	}
}

void Bomber::increaseBombLimit()
{
	bombLimit++;
}

int Bomber::getBombLimit()
{
	return bombLimit;
}

void Bomber::increaseVelocity()
{
	velocity *= 1.5f;
}

void Bomber::increaseLife()
{
	life++;
}

int Bomber::getLife()
{
	return life;
}

int Bomber::getFlamePower()
{
	return flamePower;
}

void Bomber::increaseFlamePower()
{
	flamePower++;
}
