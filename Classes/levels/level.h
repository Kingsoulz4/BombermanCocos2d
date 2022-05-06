#include "cocos2d.h"
USING_NS_CC;

class Level : public Layer
{
public:
	Level(){};
	~Level(){};
	virtual bool init();
	virtual void loadMap();
	CREATE_FUNC(Level);

private:

};

