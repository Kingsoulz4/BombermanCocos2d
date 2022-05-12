#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "characters/player/Bomber.h"
#include <vector>
#include "Definition.h"
#include "characters/enemy/LowGian.h"
#include "characters/enemy/Enemy.h"




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
	void gameOver();
	bool onContactBegin(PhysicsContact& contact);
	bool onContactEnter(PhysicsContact& contact);

	void changeEnemyDirection();
	void generateEnemies();
	
	Layer* layerBatlle;

	LowGian* lowGian = nullptr;

private:
	CCTMXTiledMap *tileMap;
	CCTMXLayer *background;
	TMXLayer* layerObject;

	Bomber *player;
	CCTMXLayer *meta;
	CCPoint tileCoordForPosition(CCPoint position);
	void setPhysicsWorld(PhysicsWorld* physicsWorld);
	PhysicsWorld* scenePhysicsWorld;

	std::vector<Enemy*> listEnemy;
	Point enemySpawnPoint;
	
};


