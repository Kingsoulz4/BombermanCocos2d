#pragma once


#include "BattleScene.h"
#include "AILow.h"


class AIHigh: public AILow
{
public:
	AIHigh();
	AIHigh(BattleScene* battleScene);

	~AIHigh();
	BattleScene* battleScene;
	std::vector<Point> findpath(Point src, Point dest);


private:

};

