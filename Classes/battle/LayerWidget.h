#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <math.h>
#include "weapons/Bomb.h"
#include "weapons/Flames.h"
#include "characters/player/Bomber.h"
#include "BattleScene.h"
#include "audio/AudioManager.h"

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
	BattleScene* battleScene;
	static LayerWidget* create(BattleScene* battleScene);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);

	double distanceRadiusJoyStick(Point destination);
	void update(float dt);


private:
	Sprite* joyStick;
	Sprite* joyStickThumbnail;
	Bomber* playerUnderControl;
	std::vector<Bomb*> bombPlaced;
	std::vector<Flames*> flamesBurning;
};

