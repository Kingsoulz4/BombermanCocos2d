#include "Bomb.h"

Bomb::Bomb()
{
}

Bomb::~Bomb()
{
}

Bomb* Bomb::create()
{
	auto ret = new (std::nothrow) Bomb;
	if (ret && ret->initWithFile("Sprites/Weapons/Bomb_03.png")) {
		ret->autorelease();
		//ret->velocity = 1.f; //declare here or in init
		ret->setScale(2);
		auto bomAnimation = Animation::create();
		bomAnimation->setLoops(-1);
		bomAnimation->setDelayPerUnit(0.15);
		bomAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/Bomb_04.png")->getSpriteFrame());
		bomAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/Bomb_05.png")->getSpriteFrame());
		bomAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/Bomb_06.png")->getSpriteFrame());
		bomAnimation->addSpriteFrame(Sprite::create("Sprites/Weapons/Bomb_07.png")->getSpriteFrame());
		auto bombAnimate = Animate::create(bomAnimation);
		ret->runAction(bombAnimate);
		ret->scheduleUpdate();
		return ret;
	}
	CC_SAFE_RELEASE(ret);
	return nullptr;
}

float Bomb::getTimeExplode()
{
	return timeExplode;
}

void Bomb::update(float dt)
{
	if (timeExplode > 0.f)
	{
		timeExplode -= dt;
	}
	else
	{
		CCLOG("bomb explode");
		//delete(this);
	}

}

bool Bomb::init()
{
	if (!Bomb::create())
	{
		return false;
	}
	this->scheduleUpdate();
	return true;
}
