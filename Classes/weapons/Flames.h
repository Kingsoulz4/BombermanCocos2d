#include "cocos2d.h"
#include "Definition.h"
USING_NS_CC;

class Flames: public Sprite
{
public:
	Flames();
	~Flames();
	static Flames* create();
	void update(float dt);
	float getTimeDouse();
	virtual bool init();


private:
	float timeDouse = FLAME_DOUSE;

};

