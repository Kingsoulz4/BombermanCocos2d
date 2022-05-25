#include "Flames.h"

Flames::Flames()
{
}

Flames::~Flames()
{
}

Flames* Flames::create()
{
	auto ret = new (std::nothrow) Flames;
	if (ret && ret->initWithFile("Sprites/Weapons/FlameVertical1.png")) {
		ret->autorelease();
		auto flameVerticalAnimation = Animation::create();
		flameVerticalAnimation->setDelayPerUnit(0.15f);
		flameVerticalAnimation->setLoops(-1);
		flameVerticalAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/FlameVertical1.png")->getSpriteFrame());
		flameVerticalAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/FlameVertical2.png")->getSpriteFrame());
		flameVerticalAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/FlameVertical3.png")->getSpriteFrame());
		flameVerticalAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/FlameVertical4.png")->getSpriteFrame());
		flameVerticalAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/FlameVertical5.png")->getSpriteFrame());
		auto flameAnimate = Animate::create(flameVerticalAnimation);
		ret->runAction(flameAnimate);
		ret->scheduleUpdate();
		auto flameVerticalPhysicBody = PhysicsBody::createBox(ret->getContentSize());
		flameVerticalPhysicBody->setCollisionBitmask(FLAME_COLLISION_BITMASK);
		flameVerticalPhysicBody->setGravityEnable(false);
		flameVerticalPhysicBody->setContactTestBitmask(true);
		flameVerticalPhysicBody->setDynamic(false);
		ret->setPhysicsBody(flameVerticalPhysicBody);
		ret->setScale(2);

		//add flame horizontal 
		auto flameHRight = Sprite::create("Sprites/Weapons/FlameHorizontal1.png");
		flameHRight->setScale(0.9);
		flameHRight->setPosition(Point(ret->getContentSize().width, ret->getContentSize().height / 1.55));
		flameHRight->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		auto flameHRightAnimation = Animation::create();
		flameHRightAnimation->setLoops(-1);
		flameHRightAnimation->setDelayPerUnit(0.15f);
		flameHRightAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/FlameHorizontal1.png")->getSpriteFrame());
		flameHRightAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/FlameHorizontal2.png")->getSpriteFrame());
		flameHRightAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/FlameHorizontal3.png")->getSpriteFrame());
		flameHRightAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/FlameHorizontal4.png")->getSpriteFrame());
		flameHRightAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/FlameHorizontal5.png")->getSpriteFrame());
		auto flameHRightAnimate = Animate::create(flameHRightAnimation);
		flameHRight->runAction(flameHRightAnimate);
		auto flameHRightPhysicBody = PhysicsBody::createBox(flameHRight->getContentSize());
		flameHRightPhysicBody->setCollisionBitmask(FLAME_COLLISION_BITMASK);
		flameHRightPhysicBody->setGravityEnable(false);
		flameHRightPhysicBody->setContactTestBitmask(true);
		flameHRightPhysicBody->setDynamic(false);
		flameHRight->setPhysicsBody(flameHRightPhysicBody);
		ret->addChild(flameHRight);

		auto flameHTopRight = Sprite::create("Sprites/Weapons/FlameTopRight1.png");
		flameHTopRight->setScale(0.9);
		flameHTopRight->setPosition(Point(flameHRight->getContentSize().width + flameHRight->getContentSize().width/1.2, ret->getContentSize().height / 1.55));
		flameHTopRight->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		auto flameHTopRightAnimation = Animation::create();
		flameHTopRightAnimation->setLoops(-1);
		flameHTopRightAnimation->setDelayPerUnit(0.15f);
		flameHTopRightAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/FlameTopRight1.png")->getSpriteFrame());
		flameHTopRightAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/FlameTopRight2.png")->getSpriteFrame());
		flameHTopRightAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/FlameTopRight3.png")->getSpriteFrame());
		flameHTopRightAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/FlameTopRight4.png")->getSpriteFrame());
		flameHTopRightAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/FlameTopRight5.png")->getSpriteFrame());
		auto flameHTopRightAnimate = Animate::create(flameHTopRightAnimation);
		flameHTopRight->runAction(flameHTopRightAnimate);
		auto flameHTopRightPhysicBody = PhysicsBody::createBox(flameHTopRight->getContentSize());
		flameHTopRightPhysicBody->setCollisionBitmask(FLAME_COLLISION_BITMASK);
		flameHTopRightPhysicBody->setGravityEnable(false);
		flameHTopRightPhysicBody->setContactTestBitmask(true);
		flameHTopRightPhysicBody->setDynamic(false);
		flameHTopRight->setPhysicsBody(flameHTopRightPhysicBody);
		ret->addChild(flameHTopRight);

		auto flameHLeft = Sprite::create("Sprites/Weapons/FlameHorizontal1.png");
		flameHLeft->setScale(0.9);
		flameHLeft->setPosition(Point(ret->getPositionX() - ret->getContentSize().width/1.14, ret->getContentSize().height / 1.55));
		flameHLeft->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		auto flameHLeftAnimation = Animation::create();
		flameHLeftAnimation->setLoops(-1);
		flameHLeftAnimation->setDelayPerUnit(0.15f);
		flameHLeftAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/FlameHorizontal1.png")->getSpriteFrame());
		flameHLeftAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/FlameHorizontal2.png")->getSpriteFrame());
		flameHLeftAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/FlameHorizontal3.png")->getSpriteFrame());
		flameHLeftAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/FlameHorizontal4.png")->getSpriteFrame());
		flameHLeftAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/FlameHorizontal5.png")->getSpriteFrame());
		auto flameHLeftAnimate = Animate::create(flameHLeftAnimation);
		flameHLeft->runAction(flameHLeftAnimate);
		auto flameHLeftPhysicBody = PhysicsBody::createBox(flameHLeft->getContentSize());
		flameHLeftPhysicBody->setCollisionBitmask(FLAME_COLLISION_BITMASK);
		flameHLeftPhysicBody->setGravityEnable(false);
		flameHLeftPhysicBody->setContactTestBitmask(true);
		flameHLeftPhysicBody->setDynamic(false);
		flameHLeft->setPhysicsBody(flameHLeftPhysicBody);
		ret->addChild(flameHLeft);

		auto flameHTopLeft = Sprite::create("Sprites/Weapons/FlameTopLeft1.png");
		flameHTopLeft->setScale(0.9);
		flameHTopLeft->setPosition(Point(flameHLeft->getPositionX() - ret->getContentSize().width / 1.14, ret->getContentSize().height / 1.55));
		flameHTopLeft->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		auto flameHTopLeftAnimation = Animation::create();
		flameHTopLeftAnimation->setLoops(-1);
		flameHTopLeftAnimation->setDelayPerUnit(0.15f);
		flameHTopLeftAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/FlameTopLeft1.png")->getSpriteFrame());
		flameHTopLeftAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/FlameTopLeft2.png")->getSpriteFrame());
		flameHTopLeftAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/FlameTopLeft3.png")->getSpriteFrame());
		flameHTopLeftAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/FlameTopLeft4.png")->getSpriteFrame());
		flameHTopLeftAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/FlameTopLeft5.png")->getSpriteFrame());
		auto flameHTopLeftAnimate = Animate::create(flameHTopLeftAnimation);
		flameHTopLeft->runAction(flameHTopLeftAnimate);
		auto flameHTopLeftPhysicBody = PhysicsBody::createBox(flameHTopLeft->getContentSize());
		flameHTopLeftPhysicBody->setCollisionBitmask(FLAME_COLLISION_BITMASK);
		flameHTopLeftPhysicBody->setGravityEnable(false);
		flameHTopLeftPhysicBody->setContactTestBitmask(true);
		flameHTopLeftPhysicBody->setDynamic(false);
		flameHTopLeft->setPhysicsBody(flameHTopLeftPhysicBody);
		ret->addChild(flameHTopLeft);



		return ret;
	}
	CC_SAFE_RELEASE(ret);
	return nullptr;
}

Flames* Flames::create(int power)
{
	auto ret = new (std::nothrow) Flames;
	if (ret && ret->initWithFile("explosions/Flame1.png")) {
		ret->autorelease();
		ret->_power = power;
		//ret->init();
		int dx[4] = {0,0,1,-1};
		int dy[4] = {1,-1,0,0};
		for (int  i = 0; i <= ret->_power; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				auto flame = Sprite::create("explosions/Flame1.png");
				flame->setScale(0.9);
				flame->setPosition(Point(ret->getPositionX() + dx[j]*(i) * (ret->getContentSize().width / 1.14), ret->getPositionY() + dy[j]*(i) * (ret->getContentSize().height / 1.14)));
				flame->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
				auto flameHTopLeftAnimation = Animation::create();
				flameHTopLeftAnimation->setLoops(-1);
				flameHTopLeftAnimation->setDelayPerUnit(0.15f);
				flameHTopLeftAnimation->addSpriteFrame(Sprite::create("explosions/Flame1.png")->getSpriteFrame());
				flameHTopLeftAnimation->addSpriteFrame(Sprite::create("explosions/Flame2.png")->getSpriteFrame());
				flameHTopLeftAnimation->addSpriteFrame(Sprite::create("explosions/Flame3.png")->getSpriteFrame());
				flameHTopLeftAnimation->addSpriteFrame(Sprite::create("explosions/Flame4.png")->getSpriteFrame());
				flameHTopLeftAnimation->addSpriteFrame(Sprite::create("explosions/Flame5.png")->getSpriteFrame());
				flameHTopLeftAnimation->addSpriteFrame(Sprite::create("explosions/Flame6.png")->getSpriteFrame());
				flameHTopLeftAnimation->addSpriteFrame(Sprite::create("explosions/Flame7.png")->getSpriteFrame());
				flameHTopLeftAnimation->addSpriteFrame(Sprite::create("explosions/Flame8.png")->getSpriteFrame());
				auto flameHTopLeftAnimate = Animate::create(flameHTopLeftAnimation);
				flame->runAction(flameHTopLeftAnimate);
				auto flameHTopLeftPhysicBody = PhysicsBody::createBox(flame->getContentSize());
				flameHTopLeftPhysicBody->setCollisionBitmask(FLAME_COLLISION_BITMASK);
				flameHTopLeftPhysicBody->setGravityEnable(false);
				flameHTopLeftPhysicBody->setContactTestBitmask(true);
				flameHTopLeftPhysicBody->setDynamic(false);
				flame->setPhysicsBody(flameHTopLeftPhysicBody);
				ret->addChild(flame);
				if (i==0)
				{
					break;
				}
			}
		}
		/*auto flamePhysicbody = PhysicsBody::createBox(ret->getContentSize());
		flamePhysicbody->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
		flamePhysicbody->setContactTestBitmask(true);
		flamePhysicbody->setGravityEnable(false);
		flamePhysicbody->setDynamic(false);*/

		/*ret->setPhysicsBody(flamePhysicbody);*/
		ret->scheduleUpdate();
		return ret;
	}
	CC_SAFE_RELEASE(ret);
	return nullptr;
}

void Flames::update(float dt)
{
	if (timeDouse > 0.f)
	{
		timeDouse -= dt;
	}
	else
	{

	}
}

float Flames::getTimeDouse()
{
	return timeDouse;
}

bool Flames::init()
{
	return false;
}
