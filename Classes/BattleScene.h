#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "characters/player/Bomber.h"
#include <vector>
#include "Definition.h"
#include "characters/enemy/LowGian.h"




USING_NS_CC;

class BattleScene : public cocos2d::Layer
{
public:

	virtual bool init();
	static Scene* createScene();
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
	// implement the "static create()" method manually
	CREATE_FUNC(BattleScene);
	void setBomber(Bomber *bomber);
	Bomber* getBomber();
	void spawnWall();
	void update(float dt);
	void changeEnemyDirection();
	LowGian* lowGian = nullptr;

private:
	CCTMXTiledMap *tileMap;
	CCTMXLayer *background;
	Bomber *player;
	CCTMXLayer *meta;
	CCPoint tileCoordForPosition(CCPoint position);
	void setPhysicsWorld(PhysicsWorld* physicsWorld);
	PhysicsWorld* scenePhysicsWorld;
	
};

#endif // __GAME_SCENE_H__
