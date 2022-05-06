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
		return ret;
	}
	CC_SAFE_RELEASE(ret);
	return nullptr;
}
