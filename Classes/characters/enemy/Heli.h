#pragma once

#include "cocos2d.h"
#include "Enemy.h"
#include "Definition.h"
#include <time.h>
#include "BattleScene.h"


class Heli: public Enemy
{
public:
	Heli();
	~Heli();
	void move() override;
	void moveNorth() override;
	void moveEast() override;
	void moveSouth() override;
	void moveWest() override;
	void changeDirection() override;
	void dead();
	void enemyDead() override;

	virtual bool init();

	static Heli* create(BattleScene* battleScene);
	void update(float dt);

private:

};

