#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Definition.h"
#include <time.h>

class LowGian : public Enemy
{
public:
	LowGian();
	~LowGian();

	void move();
	void moveNorth();
	void moveEast();
	void moveSouth();
	void moveWest();
	void changeDirection();
private:
	
};

