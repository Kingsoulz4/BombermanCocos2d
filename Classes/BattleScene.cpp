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
	tileMap->setScale(1.7);
	tileMap->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	tileMap->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	background = tileMap->layerNamed("Background");
	background->setScale(3);
	background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	background->setPosition(Point(0, 0));
	layerObject = tileMap->getLayer("Meta");
	//CCLOG("layer size: %f ",layerObject->getLayerSize().width);
	for (int i = 0; i < layerObject->getLayerSize().height; i++)
	{
		for (int j = 0; j < layerObject->getLayerSize().width; j++)
		{
			
			auto objID = layerObject->getTileGIDAt(Point(j, i));
			if (objID != 0)
			{
				auto obj = layerObject->getTileAt(Point(j, i));
				auto _physicsBody = PhysicsBody::createBox(obj->getContentSize());
				_physicsBody->setCollisionBitmask(WALL_COLLISION_BITMASK);
				_physicsBody->setGravityEnable(false);
				_physicsBody->setDynamic(false);
				_physicsBody->setContactTestBitmask(true);
				obj->setPhysicsBody(_physicsBody);
			}
			
		}
	}

	this->addChild(tileMap);
	
	
	
	//layerTileMap->setPhysicsWor

	//Player
	player = (Bomber*)Bomber::create("Sprites/Player/BomberWalkDown1.png");
	player->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
	//player->setScale(0.6);
	Size playerPhysicsBodySize = player->getContentSize();
	playerPhysicsBodySize.width *= 0.8;
	playerPhysicsBodySize.height *= 0.8;
	auto playerPhysicsBody = PhysicsBody::createBox(playerPhysicsBodySize);
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

	//Add enemy
	enemySpawnPoint = Point(200,300);
	generateEnemies();
	


	// Add widget layer
	auto layerWidget = LayerWidget::create();
	layerWidget->setPlayerUnderControl(player);
	this->addChild(layerWidget);

	//meta layer
	//meta = tileMap->layerNamed("Meta");
	//meta->setVisible(false);

	//add wall
	//spawnWall();

	//Collision event 
	auto collisionListener = EventListenerPhysicsContact::create();
	/*collisionListener->onContactBegin = [=](PhysicsContact& contact)
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
	};*/
	collisionListener->onContactBegin = CC_CALLBACK_1(BattleScene::onContactBegin, this);
	collisionListener->onContactPreSolve = CC_CALLBACK_1(BattleScene::onContactEnter, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(collisionListener,this);
	//update 
	this->scheduleUpdate();
	return true;
}

Scene* BattleScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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

void BattleScene::spawnWall()
{
	auto spawnPoint = Point(450, 150);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++) {
			auto wall1 = Sprite::create("level/Wall1.png");
			wall1->setPosition(Point(spawnPoint.x+j*TILE_SPACE, spawnPoint.y + i*TILE_SPACE));
			this->addChild(wall1);
			Size wall1PhysicsBodySize = wall1->getContentSize();
			wall1PhysicsBodySize.width *= 0.8;
			wall1PhysicsBodySize.height *= 0.8;
			auto wall1PhysicsBody = PhysicsBody::createBox(wall1PhysicsBodySize);
			wall1->setPhysicsBody(wall1PhysicsBody);
			wall1PhysicsBody->setCollisionBitmask(WALL_COLLISION_BITMASK);
			wall1PhysicsBody->setContactTestBitmask(true);
			wall1PhysicsBody->setGravityEnable(false);
			wall1PhysicsBody->setDynamic(false);
		}
	}
	
}

void BattleScene::update(float dt)
{
	//lowGian->moveSouth();
	
	background->setPosition(Point(background->getContentSize().width-player->getPositionX(), background->getContentSize().height - player->getPositionY()));

	auto ptr = listEnemy.begin();
	while (ptr < listEnemy.end())
	{
		lowGian->move();
		lowGian->changeDirection();
		if ((*ptr)->isDead)
		{
			this->removeChild((*ptr));
			listEnemy.erase(ptr);
			break;
		}
		else
		{
			ptr++;
		}
	}
	
	
}

void BattleScene::gameOver()
{
	//CCLOG("Game over");
}

bool BattleScene::onContactBegin(PhysicsContact& contact)
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
	
	auto shapeA = contact.getShapeA()->getCollisionBitmask();
	auto shapeB = contact.getShapeB()->getCollisionBitmask();
	if ((shapeA == PLAYER_COLLISION_BITMASK && shapeB == ENEMY_COLLISION_BITMASK ) ||(shapeA == ENEMY_COLLISION_BITMASK && shapeB == PLAYER_COLLISION_BITMASK) 
		|| (shapeA == PLAYER_COLLISION_BITMASK && shapeB == FLAME_COLLISION_BITMASK) || (shapeA == FLAME_COLLISION_BITMASK && shapeB == PLAYER_COLLISION_BITMASK))
	{
		gameOver();
	}
	if ((shapeA == ENEMY_COLLISION_BITMASK && shapeB == FLAME_COLLISION_BITMASK) || (shapeA == FLAME_COLLISION_BITMASK && shapeB == ENEMY_COLLISION_BITMASK))
	{
		CCLOG("Enemy dead");
		if (shapeA == ENEMY_COLLISION_BITMASK)
		{
			auto e = ((Enemy*)contact.getShapeA()->getBody()->getNode());
			e->enemyDead();

		}
		if (shapeB == ENEMY_COLLISION_BITMASK)
		{
			auto e = ((Enemy*)contact.getShapeB()->getBody()->getNode());
			e->enemyDead();
		}
	}
	return true;
}

bool BattleScene::onContactEnter(PhysicsContact& contact)
{
	auto shapeA = contact.getShapeA()->getCollisionBitmask();
	auto shapeB = contact.getShapeB()->getCollisionBitmask();
	if ((shapeA == PLAYER_COLLISION_BITMASK && shapeB == ENEMY_COLLISION_BITMASK) || (shapeA == ENEMY_COLLISION_BITMASK && shapeB == PLAYER_COLLISION_BITMASK)
		|| (shapeA == PLAYER_COLLISION_BITMASK && shapeB == FLAME_COLLISION_BITMASK) || (shapeA == FLAME_COLLISION_BITMASK && shapeB == PLAYER_COLLISION_BITMASK))
	{
		gameOver();
	}
	if ((shapeA == ENEMY_COLLISION_BITMASK && shapeB == FLAME_COLLISION_BITMASK) || (shapeA == FLAME_COLLISION_BITMASK && shapeB == ENEMY_COLLISION_BITMASK))
	{
		CCLOG("Enemy dead");
		if (shapeA == ENEMY_COLLISION_BITMASK)
		{
			auto e = ((Enemy*) contact.getShapeA()->getBody()->getNode());
			e->enemyDead();

		}
		if (shapeB == ENEMY_COLLISION_BITMASK)
		{
			auto e = ((Enemy*)contact.getShapeB()->getBody()->getNode());
			e->enemyDead();
		}
	}
	return true;
}

void BattleScene::changeEnemyDirection()
{
	lowGian->changeDirection();
}

void BattleScene::generateEnemies()
{
	lowGian = (LowGian*)LowGian::create();
	lowGian->setPosition(enemySpawnPoint);
	lowGian->setMoveDirection(MOVE_NORTH);
	listEnemy.push_back(lowGian);
	->addChild(lowGian);
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

