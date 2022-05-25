

#include "Ufo.h"
#include "ai/AIMedium.h"

//AI* ai;

Ufo::Ufo()
{
}

Ufo::~Ufo()
{
}

void Ufo::move()
{
	Enemy::move();
}

void Ufo::moveNorth()
{
	auto moveNorthAnimate = getUfoMoveAnimate();
	auto ufoWalkNorth = MoveBy::create(dtMove, Vec2(0, velocity));
	ufoWalkNorth->setTag(21);
	moveNorthAnimate->setTag(11);
	if (this->getActionByTag(11) == nullptr)
	{
		this->runAction(moveNorthAnimate);
	}
	if (this->getActionByTag(21) == nullptr)
	{
		this->runAction(ufoWalkNorth);
	}
}

void Ufo::moveEast()
{
	auto moveNorthAnimate = getUfoMoveAnimate();
	auto heliWalkNorth = MoveBy::create(dtMove, Vec2(velocity, 0));
	heliWalkNorth->setTag(22);
	moveNorthAnimate->setTag(12);
	if (this->getActionByTag(12) == nullptr)
	{
		this->runAction(moveNorthAnimate);
	}
	if (this->getActionByTag(22) == nullptr)
	{
		this->runAction(heliWalkNorth);
	}
}

void Ufo::moveSouth()
{
	
	auto moveNorthAnimate = getUfoMoveAnimate();
	auto heliWalkNorth = MoveBy::create(dtMove, Vec2(0, -velocity));
	heliWalkNorth->setTag(23);
	moveNorthAnimate->setTag(13);
	if (this->getActionByTag(13) == nullptr)
	{
		this->runAction(moveNorthAnimate);
	}
	if (this->getActionByTag(23) == nullptr)
	{
		this->runAction(heliWalkNorth);
	}
}

void Ufo::moveWest()
{
	auto moveNorthAnimate = getUfoMoveAnimate();
	auto heliWalkNorth = MoveBy::create(dtMove, Vec2(-velocity, 0));
	heliWalkNorth->setTag(24);
	moveNorthAnimate->setTag(14);
	if (this->getActionByTag(14) == nullptr)
	{
		this->runAction(moveNorthAnimate);
	}
	if (this->getActionByTag(24) == nullptr)
	{
		this->runAction(heliWalkNorth);
	}
}


void Ufo::changeDirection()
{
	isMoving = false;

	moveDirection = ai->changeDirection(moveDirection);
}

void Ufo::enemyDead()
{
	Enemy::enemyDead();
	this->stopAllActions();
	auto heliDeadAnimation = Animation::create();
	heliDeadAnimation->setDelayPerUnit(deadTime / 5);
	heliDeadAnimation->setLoops(1);
	heliDeadAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/ufoDie1.png")->getSpriteFrame());
	heliDeadAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/ufoDie2.png")->getSpriteFrame());
	heliDeadAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/ufoDie3.png")->getSpriteFrame());
	auto heliDeadAnimate = Animate::create(heliDeadAnimation);
	auto enemyDeadSequence = Sequence::create(heliDeadAnimate, CallFunc::create([=] {
		this->removeFromParent();
		}), NULL);
	this->runAction(enemyDeadSequence);
}

Animate* Ufo::getUfoMoveAnimate()
{
	auto moveAnimation = Animation::create();
	moveAnimation->setDelayPerUnit(this->dtMove);
	moveAnimation->setLoops(1);
	moveAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/ufo1.png")->getSpriteFrame());
	moveAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/ufo2.png")->getSpriteFrame());
	moveAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/ufo3.png")->getSpriteFrame());
	moveAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/ufo4.png")->getSpriteFrame());
	moveAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/ufo5.png")->getSpriteFrame());
	moveAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/ufo6.png")->getSpriteFrame());
	auto moveNorthAnimate = Animate::create(moveAnimation);
	return moveNorthAnimate;
}

bool Ufo::init()
{
	if (!Sprite::create())
	{
		return false;
	}

	ai = new AIMedium();

	return true;
}

Ufo* Ufo::create(BattleScene* battleScene)
{
	auto ret = new (std::nothrow) Ufo;
	if (ret && ret->initWithFile("Sprites/Enemies/ufo1.png")) {
		ret->autorelease();
		ret->battleScene = battleScene;
		ret->init();
		auto ufoPhysicbody = PhysicsBody::createBox(ret->getContentSize());
		ufoPhysicbody->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
		ufoPhysicbody->setContactTestBitmask(true);
		ufoPhysicbody->setGravityEnable(false);
		ufoPhysicbody->setDynamic(false);

		ret->setPhysicsBody(ufoPhysicbody);
		ret->scheduleUpdate();
		ret->timeToChangeDirection = 5.f;
		ret->moveStatus = MOVE_VIA_AILOW;
		return ret;
	}
	CC_SAFE_RELEASE(ret);
	return nullptr;
}

void Ufo::update(float dt)
{
	Enemy::update(dt);
	/*Point convertedToSceneSize = this->getPosition();
	convertedToSceneSize.x = (this->getPositionX() / battleScene->getTileMap()->getContentSize().width) * (Director::getInstance()->getVisibleSize().width);
	convertedToSceneSize.y = (this->getPositionY() / battleScene->getTileMap()->getContentSize().height) * (Director::getInstance()->getVisibleSize().height);*/
	

	if (((AIMedium*)ai)->detectTarget(this, battleScene->getBomber()) && moveStatus != MOVE_VIA_AIMEDIUM)
	{
		moveStatus = MOVE_VIA_AIMEDIUM;
	}
	else if (!((AIMedium*)ai)->detectTarget(this, battleScene->getBomber()))
	{
		moveStatus = MOVE_VIA_AILOW;

	}

	if (moveStatus == MOVE_VIA_AIMEDIUM)
	{
		float offset = velocity * 3 * battleScene->tileMapScaled;
		this->move();
		moveDirection = ((AIMedium*)ai)->calculateDirection(this, battleScene->getBomber());
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
	}


	
}

