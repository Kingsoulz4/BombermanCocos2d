#include "cocos2d.h"
#include "Definition.h"
USING_NS_CC;

class Flames: public Sprite
{
public:
	Flames();
	~Flames();
	static Flames* create();
	static Flames* create(int power);
	void update(float dt);
	float getTimeDouse();
	virtual bool init();
	int _power = 1;


private:
	float timeDouse = FLAME_DOUSE;

};

