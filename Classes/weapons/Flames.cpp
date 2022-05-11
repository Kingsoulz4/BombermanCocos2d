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
		return ret;
	}
	CC_SAFE_RELEASE(ret);
	return nullptr;
}
