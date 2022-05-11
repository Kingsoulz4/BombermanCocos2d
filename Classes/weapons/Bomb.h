#pragma once

#include "cocos2d.h"
#include "Definition.h"
USING_NS_CC;


class Bomb : public Sprite
{
public:
	Bomb();
	~Bomb();
	
	void update(float dt);
	virtual bool init();
	static Bomb* create();
	
	float getTimeExplode();

private:
	float timeExplode = TIME_BOMB_EXPLODE;

};
