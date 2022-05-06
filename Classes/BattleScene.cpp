#include "BattleScene.h"
#include "battle/LayerWidget.h"



bool BattleScene::init()
{
	if (!Layer::create())
	{
		return false;
	}
	//this->setPhysicsWorld(this->getPhysicsWorld());

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleSize();
	//tile map
	tileMap = new CCTMXTiledMap();
	tileMap->initWithTMXFile("tmx/battle1.tmx");
	tileMap->setScale(1.5);
	tileMap->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	tileMap->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(tileMap);
	//layerTileMap->setPhysicsWor

	//Player
	player = (Bomber*)Bomber::create("Sprites/Player/BomberWalkDown1.png");
	player->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
	auto playerPhysicsBody = PhysicsBody::createBox(player->getContentSize());
	playerPhysicsBody->setCollisionBitmask(PLAYER_COLLISION_BITMASK);
	playerPhysicsBody->setContactTestBitmask(true);
	playerPhysicsBody->setGravityEnable(false);
	playerPhysicsBody->setDynamic(false);
	player->setPhysicsBody(playerPhysicsBody);
	


	
	auto playerAnimation = Animation::create();
	playerAnimation->setLoops(-1);
	playerAnimation->setDelayPerUnit(1.f);
	playerAnimation->addSpriteFrame(Sprite::create("Sprites/Player/BomberWalkDown2.png")->getSpriteFrame());
	playerAnimation->addSpriteFrame(Sprite::create("Sprites/Player/BomberWalkDown3.png")->getSpriteFrame());
	playerAnimation->addSpriteFrame(Sprite::create("Sprites/Player/BomberWalkDown4.png")->getSpriteFrame());
	auto playerAnimate = Animate::create(playerAnimation);
	//player->runAction(playerAnimate);
	this->addChild(player);
	// Add widget layer
	auto layerWidget = LayerWidget::create();
	layerWidget->setPlayerUnderControl(player);
	this->addChild(layerWidget);

	//meta layer
	//meta = tileMap->layerNamed("Meta");
	//meta->setVisible(false);

	//add sprites 
	auto wall1 = Sprite::create("level/Wall1.png");
	wall1->setPosition(Point(500, 500));
	this-> addChild(wall1);
	auto wall1PhysicsBody = PhysicsBody::createBox(wall1->getContentSize());
	wall1->setPhysicsBody(wall1PhysicsBody);
	wall1PhysicsBody->setCollisionBitmask(WALL_COLLISION_BITMASK);
	wall1PhysicsBody->setContactTestBitmask(true);
	wall1PhysicsBody->setGravityEnable(false);
	wall1PhysicsBody->setDynamic(false);

	//Collision event 
	auto collisionListener = EventListenerPhysicsContact::create();
	collisionListener->onContactBegin = [=](PhysicsContact& contact)
	{
		CCLOG("Bomber collide");
		if (player->getMoveDirection() == MOVE_WEST)
		{
			player->walkEast();
		}
		if (player->getMoveDirection() == MOVE_EAST)
		{
			player->walkWest();
		}
		if (player->getMoveDirection() == MOVE_NORTH)
		{
			player->walkSouth();
		}
		if (player->getMoveDirection() == MOVE_SOUTH)
		{
			player->walkNorth();
		}
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(collisionListener,this);
	return true;
}

Scene* BattleScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = BattleScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}

bool BattleScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	return false;
}

void BattleScene::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event)
{
}

void BattleScene::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
{
}

void BattleScene::onTouchCancelled(cocos2d::Touch * touch, cocos2d::Event * event)
{
}

void BattleScene::setBomber(Bomber * bomber)
{
	player = bomber;
}

Bomber * BattleScene::getBomber()
{
	return player;
}

CCPoint BattleScene::tileCoordForPosition(CCPoint position)
{
	int x = position.x / tileMap->getTileSize().width;
	int y = ((tileMap->getMapSize().height * tileMap->getTileSize().height) - position.y) / tileMap->getTileSize().height;
	return ccp(x,y);
}

void BattleScene::setPhysicsWorld(PhysicsWorld* physicsWorld)
{
	scenePhysicsWorld = physicsWorld;
}

