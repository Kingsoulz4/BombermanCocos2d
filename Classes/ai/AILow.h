#pragma once

#include "AI.h"

class AILow: public AI
{
public:
	AILow();
	~AILow ();

	int changeDirection(int oldDir) override;

private:

};

