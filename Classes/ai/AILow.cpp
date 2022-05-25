#include "AILow.h"

AILow::AILow()
{
}

AILow::~AILow()
{
}

int AILow::changeDirection(int oldDir)
{
	srand(time(NULL));
	int t;
	do
	{
		t = randRange(11, 14);
	} while (t == oldDir);
	return t;

}
