#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "characters/player/Bomber.h"
#include <vector>


USING_NS_CC;

class BattleScene : public cocos2d::Scene
{
public:

	virtual bool init();

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
	// implement the "static create()" method manually
	CREATE_FUNC(BattleScene);
	void setBomber(Bomber *bomber);
	Bomber* getBomber();


private:
	CCTMXTiledMap *tileMap;
	CCTMXLayer *background;
	Bomber *player;
	CCTMXLayer *meta;
	CCPoint tileCoordForPosition(CCPoint position);
};

#endif // __GAME_SCENE_H__
