#pragma once

#include "cocos2d.h"
#include "AILow.h"
#include "Definition.h"

class AIMedium: public AILow
{
public:
	AIMedium();
	~AIMedium();


	int changeDirection(int oldDir) override;
	bool detectTarget(Sprite* self, Sprite* target);
	bool detectTarget(Point self, Point target);
	int calculateDirection(Sprite* self, Sprite* target);



private:

};

