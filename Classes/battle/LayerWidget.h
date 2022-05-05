#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <math.h>
#include "characters/player/Bomber.h"

USING_NS_CC;

class LayerWidget: public Layer
{
public:


	LayerWidget();
	~LayerWidget();

	virtual bool init();
	void setPlayerUnderControl(Bomber* bomber);
	Bomber* getPlayerUnderControl();
	// implement the "static create()" method manually
	CREATE_FUNC(LayerWidget);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);

	double distanceRadiusJoyStick(Point destination);


private:
	Sprite* joyStick;
	Sprite* joyStickThumbnail;
	Bomber* playerUnderControl;
};

