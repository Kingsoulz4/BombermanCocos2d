#include "Definition.h"

int getDirection(float cosA, float sinA)
{
	if (cosA >= sqrt(2) / 2 && cosA <= 1)
	{

		return MOVE_EAST;
	}
	else if (cosA <= sqrt(2) / 2 && cosA >= -sqrt(2) / 2)
	{
		if (sinA > 0)
		{
			return MOVE_NORTH;
		}
		else if (sinA < 0)
		{
			return MOVE_SOUTH;
		}

	}
	else if (cosA <= -sqrt(2) / 2 && cosA >= -1)
	{
		return MOVE_WEST;
	}
}
