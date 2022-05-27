#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "characters/player/Bomber.h"
#include <vector>
#include "Definition.h"
#include "characters/player/Bomber.h"
#include "audio/AudioManager.h"

USING_NS_CC;


class BattleScene : public cocos2d::Layer
{

public:
	Cam cam;
	virtual bool init();
	static Scene* createScene(int level);
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
	// implement the "static create()" method manually
	//CREATE_FUNC(BattleScene);
	static BattleScene* create(int level);
	void setBomber(Bomber *bomber);
	Bomber* getBomber();
	void spawnWall();
	void update(float dt);
	void gameOver();
	void gamePause();
	void gameWin();
	void gameResume();
	bool onContactBegin(PhysicsContact& contact);
	bool onContactEnter(PhysicsContact& contact);

	void changeEnemyDirection();
	void generateEnemies();
	void setColliderToObjectlayer(TMXLayer* layer, int collisionBitmask);
	void addColliderToTileMap();
	void getTileMapComponents();
	Point tileCoordForPosition(Point point);
	Point positionForTileCoord(Point point);
	bool detectCollision(Point point);

	TMXTiledMap* getTileMap();
	CCTMXLayer* getLayerground();
	TMXLayer* getLayerFrame();
	TMXLayer* getLayerObstacle();
	TMXLayer* getLayerContainer();
	CCTMXObjectGroup* getEntryPoints();
	
	Layer* layerBatlle;
	Node* currentTarget = nullptr;
	float tileMapScaled = 1.f;
	bool _isPause = false;
	

	

private:
	CCTMXTiledMap *tileMap;
	CCTMXLayer *layerground;
	TMXLayer* layerFrame;
	TMXLayer* layerObstacle;
	TMXLayer* layerContainer;
	CCTMXObjectGroup* entryPoints;
	TMXLayer* layerItem;

	Bomber *player;
	CCTMXLayer *meta;
	void setPhysicsWorld(PhysicsWorld* physicsWorld);
	PhysicsWorld* scenePhysicsWorld;

	int level = 1;
	Point enemySpawnPoint;
	
};


