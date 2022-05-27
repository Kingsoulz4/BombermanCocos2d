#pragma once

#include "LowGian.h"
#include "ai/AIHigh.h"

LowGian::LowGian()
{
}

LowGian::~LowGian()
{
}

void LowGian::move()
{
	//Enemy::move();
	if (moveStatus == MOVE_VIA_AIHIGH && !battleScene->getBomber()->_isDead)
	{
		moveStatus = MOVE_VIA_IDLE;
		auto ai = new AIHigh(battleScene);
		auto e3 = battleScene->getBomber();
		Point pe3 = battleScene->tileCoordForPosition(Point(e3->getPositionX(), e3->getPositionY()));
		/*auto e3 = battleScene->getTileMap()->getObjectGroup("EntryPoints")->getObject("E3");
		auto pe3 = battleScene->tileCoordForPosition(Point(e3.at("x").asInt(), e3.at("y").asInt()));*/
		auto pe2 = battleScene->tileCoordForPosition(this->getPosition());
		auto path = ai->findpath(pe2, pe3);
		if (path.size() == 0)
		{
			return;
		}
		Vector<FiniteTimeAction*> fta;
		auto fromPos = this->getPosition();
		Point toPos;
		for (int i = 0; i < path.size(); i++)
		{
			if (i > 1)
			{
				fromPos = toPos;
			}
			toPos = battleScene->positionForTileCoord(path[path.size() - 1 - i]);
			
			auto moveTo = MoveTo::create(dtMove, toPos);
			if (toPos.x > fromPos.x)
			{
				auto moveEastAnimation = Animation::create();
				moveEastAnimation->setDelayPerUnit(ANIMATION_DELAY_PER_UNIT);
				moveEastAnimation->setLoops(dtMove/(ANIMATION_DELAY_PER_UNIT*4));
				moveEastAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/LowGianMoveHorizontally1.png")->getSpriteFrame());
				moveEastAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/LowGianMoveHorizontally2.png")->getSpriteFrame());
				moveEastAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/LowGianMoveHorizontally3.png")->getSpriteFrame());
				moveEastAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/LowGianMoveHorizontally4.png")->getSpriteFrame());
				auto moveEastAnimate = Animate::create(moveEastAnimation);
				fta.pushBack(Spawn::createWithTwoActions(moveTo, moveEastAnimate));
			}

			else if (toPos.x < fromPos.x)
			{
				auto moveEastAnimation = Animation::create();
				moveEastAnimation->setDelayPerUnit(ANIMATION_DELAY_PER_UNIT);
				moveEastAnimation->setLoops(dtMove / (ANIMATION_DELAY_PER_UNIT * 4));
				moveEastAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/LowGianMoveHorizontally1.png")->getSpriteFrame());
				moveEastAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/LowGianMoveHorizontally2.png")->getSpriteFrame());
				moveEastAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/LowGianMoveHorizontally3.png")->getSpriteFrame());
				moveEastAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/LowGianMoveHorizontally4.png")->getSpriteFrame());
				auto moveEastAnimate = Animate::create(moveEastAnimation);
				fta.pushBack(Spawn::createWithTwoActions(moveTo, moveEastAnimate));
			}

			else if (toPos.y > fromPos.y)
			{
				auto moveNorthAnimation = Animation::create();
				moveNorthAnimation->setDelayPerUnit(ANIMATION_DELAY_PER_UNIT);
				moveNorthAnimation->setLoops(dtMove / (ANIMATION_DELAY_PER_UNIT * 2));
				moveNorthAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/LowGianMoveVertically1.png")->getSpriteFrame());
				moveNorthAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/LowGianMoveVertically4.png")->getSpriteFrame());
				auto moveNorthAnimate = Animate::create(moveNorthAnimation);
				fta.pushBack(Spawn::createWithTwoActions(moveTo, moveNorthAnimate));
				
			}

			else if (toPos.y < fromPos.y)
			{
				auto moveSouthAnimation = Animation::create();
				moveSouthAnimation->setDelayPerUnit(ANIMATION_DELAY_PER_UNIT);
				moveSouthAnimation->setLoops(dtMove / (ANIMATION_DELAY_PER_UNIT * 2));
				moveSouthAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/LowGianMoveVertically2.png")->getSpriteFrame());
				moveSouthAnimation->addSpriteFrame(Sprite::create("Sprites/Enemies/LowGianMoveVertically3.png")->getSpriteFrame());
				auto moveSouthAnimate = Animate::create(moveSouthAnimation);
				fta.pushBack(Spawn::createWithTwoActions(moveTo, moveSouthAnimate));
			}
			//fta.pushBack(moveTo);
			

		}
		this->runAction(Sequence::create(Sequence::create(fta), CallFunc::create([=] {
			moveStatus = MOVE_VIA_AIHIGH;
		}), NULL));
		auto pos = this->getPosition();
	}
	
}

void LowGian::moveNorth()
{
	//moveDirection = MOVE_NORTH;
	//this->stopAllActions(); 	BomberSquad.exe!LowGian::move() Line 21	C++

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
	//this->stopAllActions();
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
	//this->stopAllActions();
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
	//this->stopAllActions();
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
	//this->stopAllActions();
	isMoving = false;
	srand(time(NULL));
	int t = rand() % 4 + 11;
	while (t == moveDirection)
	{
		t = rand() % 4 + 11;
	}
	moveDirection = t;
	

}

void LowGian::enemyDead()
{
	Enemy::enemyDead();
	this->removeFromParent();
}

LowGian* LowGian::create(BattleScene* battleScene)
{
	
	auto ret = new (std::nothrow) LowGian;
	if (ret && ret->initWithFile("Sprites/Enemies/LowGianMoveHorizontally1.png")) {
		ret->autorelease();
		ret->battleScene = battleScene;
		auto lowGianPhysicbody = PhysicsBody::createBox(ret->getContentSize());
		lowGianPhysicbody->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
		lowGianPhysicbody->setContactTestBitmask(true);
		lowGianPhysicbody->setGravityEnable(false);
		lowGianPhysicbody->setDynamic(false);
		
		ret->setPhysicsBody(lowGianPhysicbody);
		ret->scheduleUpdate();
		ret->moveStatus = MOVE_VIA_AIHIGH;
		/*ret->schedule([=](float dt) {
			
			ret->changeDirection();
			}, 1.2f, "LowGianMove");*/
		return ret;
	}
	CC_SAFE_RELEASE(ret);
	return nullptr;
}

void LowGian::update(float dt)
{
	//Enemy::update(dt);
	this->move();
	CCLOG("LowGian update");
}
