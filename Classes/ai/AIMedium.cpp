#include "AIMedium.h"
#include "Definition.h"

AIMedium::AIMedium()
{
}

AIMedium::~AIMedium()
{
}

int AIMedium::changeDirection(int oldDir)
{
	return AILow::changeDirection(oldDir);
}

bool AIMedium::detectTarget(Sprite* self, Sprite* target)
{
	auto d = sqrt(pow(self->getPositionX() - target->getPositionX(), 2) + pow(self->getPositionY() - target->getPositionY(), 2));
	//CCLOG("distance to target %f", d);
	if (d <= ENEMY_VISION)
	{
		return true;
	}
	return false;
}

bool AIMedium::detectTarget(Point self, Point target)
{
	auto d = sqrt(pow(self.x  -target.x, 2) + pow(self.y - target.y, 2));
	//CCLOG("distance to target %f", d);
	if (d <= ENEMY_VISION)
	{
		return true;
	}
	return false;
}

int AIMedium::calculateDirection(Sprite* self, Sprite* target)
{
	auto distance = sqrt(pow(self->getPositionX() - target->getPositionX(), 2) + pow(self->getPositionY() - target->getPositionY(), 2));
	float offset = 50;
	if (sqrt(pow(self->getPositionX() + offset - target->getPositionX(), 2) + pow(self->getPositionY() - target->getPositionY(), 2)) < distance)
	{
		return MOVE_EAST;
	}
	else if (sqrt(pow(self->getPositionX() - offset - target->getPositionX(), 2) + pow(self->getPositionY() - target->getPositionY(), 2)) < distance)
	{
		return MOVE_WEST;
	}
	else if (sqrt(pow(self->getPositionX() - target->getPositionX(), 2) + pow(self->getPositionY()+ offset - target->getPositionY(), 2)) < distance)
	{
		return MOVE_NORTH;
	}

	return MOVE_SOUTH;
}



