#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Definition.h"
#include <time.h>
#include "BattleScene.h"

class LowGian : public Enemy
{
public:
	LowGian();
	~LowGian();

	void move() override;
	void moveNorth() override;
	void moveEast() override;
	void moveSouth() override;
	void moveWest() override;
	void changeDirection() override;
	void enemyDead() override;
	
	static LowGian* create(BattleScene *battleScene);
	void update(float dt);

private:
	
};

