#include "Heli.h"
#include "ai/AILow.h"

//AILow* ai;

Heli::Heli()
{
}

Heli::~Heli()
{
}

void Heli::move()
{
	Enemy::move();
}

void Heli::moveNorth()
{
	auto moveNorthAnimation = Animation::create();
	moveNorthAnimation->setDelayPerUnit(dtMove);
	moveNorthAnimation->setLoops(1);
	moveNorthAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/heliUp1.png")->getSpriteFrame());
	moveNorthAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/heliUp2.png")->getSpriteFrame());
	moveNorthAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/heliUp3.png")->getSpriteFrame());
	moveNorthAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/heliUp4.png")->getSpriteFrame());

	auto moveNorthAnimate = Animate::create(moveNorthAnimation);
	auto heliWalkNorth = MoveBy::create(dtMove, Vec2(0, velocity));
	heliWalkNorth->setTag(21);
	moveNorthAnimate->setTag(11);
	if (this->getActionByTag(11) == nullptr)
	{
		this->runAction(moveNorthAnimate);
	}
	if (this->getActionByTag(21) == nullptr)
	{
		this->runAction(heliWalkNorth);
	}
}

void Heli::moveEast()
{
	auto moveNorthAnimation = Animation::create();
	moveNorthAnimation->setDelayPerUnit(dtMove);
	moveNorthAnimation->setLoops(1);
	moveNorthAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/heliRight1.png")->getSpriteFrame());
	moveNorthAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/heliRight2.png")->getSpriteFrame());
	moveNorthAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/heliRight3.png")->getSpriteFrame());
	moveNorthAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/heliRight4.png")->getSpriteFrame());

	auto moveNorthAnimate = Animate::create(moveNorthAnimation);
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

void Heli::moveSouth()
{
	auto moveNorthAnimation = Animation::create();
	moveNorthAnimation->setDelayPerUnit(dtMove);
	moveNorthAnimation->setLoops(1);
	moveNorthAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/heliDown1.png")->getSpriteFrame());
	moveNorthAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/heliDown2.png")->getSpriteFrame());
	moveNorthAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/heliDown3.png")->getSpriteFrame());
	moveNorthAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/heliDown4.png")->getSpriteFrame());

	auto moveNorthAnimate = Animate::create(moveNorthAnimation);
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

void Heli::moveWest()
{
	auto moveNorthAnimation = Animation::create();
	moveNorthAnimation->setDelayPerUnit(dtMove);
	moveNorthAnimation->setLoops(1);
	moveNorthAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/heliLeft1.png")->getSpriteFrame());
	moveNorthAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/heliLeft2.png")->getSpriteFrame());
	moveNorthAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/heliLeft3.png")->getSpriteFrame());
	moveNorthAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/heliLeft4.png")->getSpriteFrame());

	auto moveNorthAnimate = Animate::create(moveNorthAnimation);
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

void Heli::changeDirection()
{
	//this->stopAllActions();
	isMoving = false;
	
	moveDirection = ai->changeDirection(moveDirection);

}

void Heli::dead()
{

	
}

void Heli::enemyDead()
{
	Enemy::enemyDead();
	this->stopAllActions();
	auto heliDeadAnimation = Animation::create();
	heliDeadAnimation->setDelayPerUnit(deadTime / 5);
	heliDeadAnimation->setLoops(1);
	heliDeadAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/heliDead1.png")->getSpriteFrame());
	heliDeadAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/heliDead2.png")->getSpriteFrame());
	heliDeadAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/heliDead3.png")->getSpriteFrame());
	heliDeadAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/heliDead4.png")->getSpriteFrame());
	auto heliDeadAnimate = Animate::create(heliDeadAnimation);
	auto enemyDeadSequence = Sequence::create(heliDeadAnimate,CallFunc::create([=] {
		this->removeFromParent();
	}), NULL);
	this->runAction(enemyDeadSequence);
}

bool Heli::init()
{
	if (!Sprite::create())
	{
		return false;
	}

	ai = new AILow();

	return true;
}

Heli* Heli::create(BattleScene* battleScene)
{
	auto ret = new (std::nothrow) Heli;
	if (ret && ret->initWithFile("Sprites/Enemies/heliLeft4.png")) {
		ret->autorelease();
		ret->battleScene = battleScene;
		ret->init();
		auto HeliPhysicbody = PhysicsBody::createBox(ret->getContentSize());
		HeliPhysicbody->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
		HeliPhysicbody->setContactTestBitmask(true);
		HeliPhysicbody->setGravityEnable(false);
		HeliPhysicbody->setDynamic(false);

		ret->setPhysicsBody(HeliPhysicbody);
		ret->scheduleUpdate();
		ret->timeToChangeDirection = 5.f;
		return ret;
	}
	CC_SAFE_RELEASE(ret);
	return nullptr;
}

void Heli::update(float dt)
{
	Enemy::update(dt);
}
