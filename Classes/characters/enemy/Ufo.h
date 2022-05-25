#pragma  once

#include "Enemy.h"

class Ufo: public Enemy
{
public:
	Ufo();
	~Ufo();
	void move() override;
	void moveNorth() override;
	void moveEast() override;
	void moveSouth() override;
	void moveWest() override;
	void changeDirection() override;
	void enemyDead() override;
	Animate* getUfoMoveAnimate();

	virtual bool init();

	static Ufo* create(BattleScene* battleScene);
	void update(float dt);

private:

};

