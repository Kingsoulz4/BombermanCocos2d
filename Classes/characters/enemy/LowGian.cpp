#pragma once

#include "LowGian.h"

LowGian::LowGian()
{
}

LowGian::~LowGian()
{
}

void LowGian::move()
{
	dtMove = 0.15f;
	velocity = 5.f;
	if (moveDirection == MOVE_NORTH)
	{
		moveNorth();
	}
	if (moveDirection == MOVE_EAST)
	{
		moveEast();
	}
	if (moveDirection == MOVE_WEST)
	{
		moveWest();
	}
	if (moveDirection == MOVE_SOUTH)
	{
		moveSouth();
	}
}

void LowGian::moveNorth()
{
	//moveDirection = MOVE_NORTH;
	auto moveNorthAnimation = Animation::create();
	moveNorthAnimation->setDelayPerUnit(dtMove);
	moveNorthAnimation->setLoops(1);
	moveNorthAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/LowGianMoveVertically1.png")->getSpriteFrame());
	moveNorthAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/LowGianMoveVertically4.png")->getSpriteFrame());
	auto moveNorthAnimate = Animate::create(moveNorthAnimation);
	auto lowGianWalkNorth = MoveBy::create(dtMove, Vec2(0, velocity));
	lowGianWalkNorth->setTag(21);
	moveNorthAnimate->setTag(11);
	if (this->getActionByTag(11) == nullptr)
	{
		this->runAction(moveNorthAnimate);
	}
	if (this->getActionByTag(21) == nullptr)
	{
		this->runAction(lowGianWalkNorth);
	}
}

void LowGian::moveEast()
{
	//moveDirection = MOVE_EAST;
	auto moveEastAnimation = Animation::create();
	moveEastAnimation->setDelayPerUnit(dtMove);
	moveEastAnimation->setLoops(1);
	moveEastAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/LowGianMoveHorizontally1.png")->getSpriteFrame());
	moveEastAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/LowGianMoveHorizontally2.png")->getSpriteFrame());
	moveEastAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/LowGianMoveHorizontally3.png")->getSpriteFrame());
	moveEastAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/LowGianMoveHorizontally4.png")->getSpriteFrame());
	auto moveEastAnimate = Animate::create(moveEastAnimation);
	auto lowGianWalkEast = MoveBy::create(dtMove, Vec2(velocity , 0));
	lowGianWalkEast->setTag(22);
	moveEastAnimate->setTag(12);
	if (this->getActionByTag(12) == nullptr)
	{
		this->runAction(moveEastAnimate);
	}
	if (this->getActionByTag(22) == nullptr)
	{
		this->runAction(lowGianWalkEast);
	}
}

void LowGian::moveSouth()
{
	//moveDirection = MOVE_SOUTH;
	auto moveSouthAnimation = Animation::create();
	moveSouthAnimation->setDelayPerUnit(dtMove);
	moveSouthAnimation->setLoops(1);
	moveSouthAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/LowGianMoveVertically2.png")->getSpriteFrame());
	moveSouthAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/LowGianMoveVertically3.png")->getSpriteFrame());
	auto moveSouthAnimate = Animate::create(moveSouthAnimation);
	auto lowGianWalkSouth = MoveBy::create(dtMove, Vec2(0, -velocity));
	lowGianWalkSouth->setTag(23);
	moveSouthAnimate->setTag(13);
	if (this->getActionByTag(13) == nullptr)
	{
		this->runAction(moveSouthAnimate);
	}
	if (this->getActionByTag(23) == nullptr)
	{
		this->runAction(lowGianWalkSouth);
	}
}

void LowGian::moveWest()
{
	//moveDirection = MOVE_WEST;
	auto moveEastAnimation = Animation::create();
	moveEastAnimation->setDelayPerUnit(dtMove);
	moveEastAnimation->setLoops(1);
	moveEastAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/LowGianMoveHorizontally1.png")->getSpriteFrame());
	moveEastAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/LowGianMoveHorizontally2.png")->getSpriteFrame());
	moveEastAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/LowGianMoveHorizontally3.png")->getSpriteFrame());
	moveEastAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/LowGianMoveHorizontally4.png")->getSpriteFrame());
	auto moveEastAnimate = Animate::create(moveEastAnimation);
	auto lowGianWalkEast = MoveBy::create(dtMove, Vec2(-velocity, 0));
	lowGianWalkEast->setTag(24);
	moveEastAnimate->setTag(14);
	if (this->getActionByTag(14) == nullptr)
	{
		this->runAction(moveEastAnimate);
	}
	if (this->getActionByTag(24) == nullptr)
	{
		this->runAction(lowGianWalkEast);
	}
}

void LowGian::changeDirection()
{
	srand(time(NULL));
	int t = rand() % 14 + 11;
	while (t == moveDirection)
	{
		t = rand() % 14 + 11;
	}
	moveDirection = t;

}

LowGian* LowGian::create()
{
	auto ret = new (std::nothrow) LowGian;
	if (ret && ret->initWithFile("Sprites/Enemies/LowGianMoveHorizontally1.png")) {
		ret->autorelease();
		auto lowGianPhysicbody = PhysicsBody::createBox(ret->getContentSize());
		lowGianPhysicbody->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
		lowGianPhysicbody->setContactTestBitmask(true);
		lowGianPhysicbody->setGravityEnable(false);
		lowGianPhysicbody->setDynamic(false);
		
		ret->setPhysicsBody(lowGianPhysicbody);
		return ret;
	}
	CC_SAFE_RELEASE(ret);
	return nullptr;
}
