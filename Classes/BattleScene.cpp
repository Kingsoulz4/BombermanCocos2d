#include "BattleScene.h"
#include "battle/LayerWidget.h"
#include "characters/enemy/LowGian.h"
#include "characters/enemy/Enemy.h"
#include "characters/enemy/Heli.h"
#include "characters/enemy/Ufo.h"
#include "ai/AIHigh.h"

std::vector<Enemy*> listEnemy;



bool BattleScene::init()
{
	if (!Layer::create())
	{
		return false;
	}
	this->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	layerBatlle = Layer::create();
	//this->addChild(layerBatlle);
	layerBatlle->setZOrder(10);

	//this->setPhysicsWorld(this->getPhysicsWorld());

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	this->setContentSize(visibleSize);
	//tile map
	tileMap = new CCTMXTiledMap();
	tileMap->initWithTMXFile("tmx/battle2.tmx");
	tileMap->addChild(layerBatlle);
	//tileMap->setScale(0.67);
	tileMap->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	Size tileMapsize;
	tileMapsize.width = tileMap->getMapSize().width*tileMap->getTileSize().width;
	tileMapsize.height = tileMap->getMapSize().height * tileMap->getTileSize().height;
	tileMapScaled = tileMap->getContentSize().width / tileMapsize.width;
	//tileMap->setContentSize(size);
	/*CCLOG("tile map width: %f", tileMap->getContentSize().width);
	CCLOG("tile map height: %f", tileMap->getContentSize().height);*/
	
	tileMap->setPosition(Point(0, 0));

	this->addChild(tileMap);

	getTileMapComponents();
	//layerBatlle->setContentSize(Size(1824, 864));
	layerBatlle->setPosition(tileMap->getPosition());
	//layerBatlle->addChild(background);
	layerBatlle->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	layerBatlle->setPosition(Point(0, 0));
	//layerBatlle->addChild(layerObject);
	// add Collider to Tile map 
	addColliderToTileMap();

	//CCLOG("layer size: %f ",layerObject->getLayerSize().width);
	


	
	
	//layerTileMap->setPhysicsWor

	//Player
	player = (Bomber*)Bomber::create();
	auto e3 = tileMap->getObjectGroup("EntryPoints")->getObject("E3");
	player->setPosition(Point(e3.at("x").asInt(), e3.at("y").asInt()));
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
	layerBatlle->addChild(player);

	//Add enemy
	/*auto enemyEntryPoint = entryPoints->getObject("TopLeft");
	CCLOG("enemy pos x %i", enemyEntryPoint.at("x").asInt());
	CCLOG("enemy pos y %i", enemyEntryPoint.at("y").asInt());

	enemySpawnPoint = Vec2(enemyEntryPoint.at("x").asInt(), enemyEntryPoint.at("y").asInt());*/
	generateEnemies();
	


	// Add widget layer
	auto layerWidget = LayerWidget::create(this);
	layerWidget->setPlayerUnderControl(player);
	this->addChild(layerWidget);

	//meta layer
	//meta = tileMap->layerNamed("Meta");
	//meta->setVisible(false);

	//add wall
	//spawnWall();

	//Collision event 
	auto collisionListener = EventListenerPhysicsContact::create();
	collisionListener->onContactBegin = CC_CALLBACK_1(BattleScene::onContactBegin, this);
	collisionListener->onContactPreSolve = CC_CALLBACK_1(BattleScene::onContactBegin, this);
	//collisionListener->onContactPostSolve = CC_CALLBACK_1(BattleScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(collisionListener,this);
	//update 
	this->scheduleUpdate();
	//ai = new AIHigh(this);
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

	auto playerMoveDirection = player->getMoveDirection();
	if (player->_canMove)
	{
		if (playerMoveDirection == MOVE_EAST)
		{
			cam.posX -= player->getVelocity() / 10;
		}
		if (playerMoveDirection == MOVE_WEST)
		{
			cam.posX += player->getVelocity() / 10;
		}
		if (playerMoveDirection == MOVE_NORTH)
		{
			cam.posY -= player->getVelocity() / 10;
		}
		if (playerMoveDirection == MOVE_SOUTH)
		{
			cam.posY += player->getVelocity() / 10;
		}
	}
	
	tileMap->setPosition(Point(cam.posX,cam.posY));
	//layerBatlle->setPosition(Point(cam.posX, cam.posY));
	//CCLOG("tile map pos x: %f", tileMap->getPositionX());
	//CCLOG("tile map pos y: %f", tileMap->getPositionY());
	

	auto ptr = listEnemy.begin();
	while (ptr < listEnemy.end())
	{
		
		if ((*ptr)->isDead)
		{
			listEnemy.erase(ptr);
			break;
		}
		else
		{
			ptr++;
		}
	}
	
	//CCLOG("Bomber collide");
	float offset = player->getVelocity() * 3 * this->tileMapScaled;
	
	if (playerMoveDirection == MOVE_EAST && detectCollision(Point(player->getPositionX() + offset, player->getPositionY())))
	{
		player->setPositionX(player->getPositionX() - player->getVelocity());
		cam.posX -= player->getVelocity()/2;
		
	}
	else if (playerMoveDirection == MOVE_WEST && detectCollision(Point(player->getPositionX() - offset, player->getPositionY())))
	{
		player->setPositionX(player->getPositionX() + player->getVelocity());
		cam.posX += player->getVelocity()/2;
		player->_canMove = false;
	}
	else if (playerMoveDirection == MOVE_NORTH && detectCollision(Point(player->getPositionX() , player->getPositionY() + offset)))
	{
		player->setPositionY(player->getPositionY() - player->getVelocity());
		cam.posY -= player->getVelocity()/2;
		player->_canMove = false;
	}
	else if (playerMoveDirection == MOVE_SOUTH && detectCollision(Point(player->getPositionX(), player->getPositionY() - offset)))
	{
		player->setPositionY(player->getPositionY() + player->getVelocity());
		cam.posY += player->getVelocity()/2;
		player->_canMove = false;
	}
	else
	{
		player->_canMove = true;
	}
	

}

void BattleScene::gameOver()
{
	//CCLOG("Game over");
	AudioManger::getInstance()->playGameOver();
}

void BattleScene::gamePause()
{
	this->pause();
	layerBatlle->pause();
	player->pause();
	//this->setCameraMask(-1, true);
	for (auto e : listEnemy)
	{
		e->pause();
	}
	
}

bool BattleScene::onContactBegin(PhysicsContact& contact)
{
	
	
	auto shapeA = contact.getShapeA()->getCollisionBitmask();
	auto shapeB = contact.getShapeB()->getCollisionBitmask();
	
	
	if ((shapeA == PLAYER_COLLISION_BITMASK && shapeB == ENEMY_COLLISION_BITMASK ) ||(shapeA == ENEMY_COLLISION_BITMASK && shapeB == PLAYER_COLLISION_BITMASK) 
		|| (shapeA == PLAYER_COLLISION_BITMASK && shapeB == FLAME_COLLISION_BITMASK) || (shapeA == FLAME_COLLISION_BITMASK && shapeB == PLAYER_COLLISION_BITMASK))
	{
		player->dead();
		gameOver();
	}
	
	if ((shapeA == ENEMY_COLLISION_BITMASK && shapeB == FLAME_COLLISION_BITMASK) || (shapeA == FLAME_COLLISION_BITMASK && shapeB == ENEMY_COLLISION_BITMASK))
	{
		CCLOG("Enemy dead");
		if (shapeA == ENEMY_COLLISION_BITMASK)
		{
			auto e = ((Enemy*)contact.getShapeA()->getBody()->getNode());
			
			if (e)
			{
				e->enemyDead();
			}

		}
		if (shapeB == ENEMY_COLLISION_BITMASK)
		{
			auto e = ((Enemy*)contact.getShapeB()->getBody()->getNode());
			if (e)
			{
				e->enemyDead();
			}
			
		}
	}

	if ((shapeA == CONTAINER_COLLISION_BITMASK && shapeB == FLAME_COLLISION_BITMASK) || (shapeA == FLAME_COLLISION_BITMASK && shapeB == CONTAINER_COLLISION_BITMASK))
	{
		
		if (shapeA == CONTAINER_COLLISION_BITMASK)
		{
			auto e = contact.getShapeA()->getBody()->getNode();
			if (e)
			{
				e->removeFromParent();
			}

		}
		if (shapeB == CONTAINER_COLLISION_BITMASK)
		{
			auto e = contact.getShapeB()->getBody()->getNode();
			if (e)
			{
				e->removeFromParent();
			}
		}
	}

	//Bomber collide item
	if ((shapeA == PLAYER_COLLISION_BITMASK && shapeB == ITEM_COLLISION_BITMASK) || (shapeA == ITEM_COLLISION_BITMASK && shapeB == PLAYER_COLLISION_BITMASK))
	{
		AudioManger::getInstance()->playItemCollected();
		if (shapeA == PLAYER_COLLISION_BITMASK)
		{
			auto shape = contact.getShapeB()->getBody()->getNode();
			if (shape)
			{
				for (int i = 0; i < layerItem->getLayerSize().height; i++)
				{
					for (int j = 0; j < layerItem->getLayerSize().width; j++)
					{
						if (layerItem->tileAt(Point(j, i)) == shape)
						{
							auto v = tileMap->propertiesForGID(layerItem->getTileGIDAt(Point(j, i))).asValueMap();
							auto y = v["itemType"].asInt();
							player->useItem(y);
							shape->removeFromParent();
							return true;
						}
					}
				}
				shape->removeFromParent();
			}
		}
		if (shapeB == PLAYER_COLLISION_BITMASK)
		{
			auto shape = contact.getShapeA()->getBody()->getNode();
			if (shape)
			{
				for (int i = 0; i < layerItem->getLayerSize().height; i++)
				{
					for (int j = 0; j < layerItem->getLayerSize().width; j++)
					{
						if (layerItem->tileAt(Point(j, i)) == shape)
						{
							auto v = tileMap->propertiesForGID(layerItem->getTileGIDAt(Point(j, i))).asValueMap();
							auto y = v["itemType"].asInt();
							player->useItem(y);
							shape->removeFromParent();
							return true;
						}
					}
				}
				
			}
			
		}
	}


	return true;
}

void BattleScene::changeEnemyDirection()
{
	
	auto e3 = this->getEntryPoints()->getObject("E3");
	Point pe3 = tileCoordForPosition(Point(e3.at("x").asInt(), e3.at("y").asInt()));
	auto e5 = this->getEntryPoints()->getObject("E5");
	Point pe5 = tileCoordForPosition(Point(e5.at("x").asInt(), e5.at("y").asInt()));
	
}

void BattleScene::generateEnemies()
{
	
	auto epoints = entryPoints->getObjects();
	for  (auto obj : epoints)
	{
		auto eSpawnPoint = Vec2(obj.asValueMap().at("x").asInt(), obj.asValueMap().at("y").asInt());
		auto name = obj.asValueMap()["name"].asString();
		int p = name.find("L");
		if (name.find("L") != std::string::npos)
		{
			//auto e = (Heli*)Heli::create(this);
			auto e = (LowGian*)LowGian::create(this);
			//auto e = (Ufo*)Ufo::create(this);
			e->setPosition(eSpawnPoint);
			e->setMoveDirection(MOVE_NORTH);
			listEnemy.push_back(e);
			layerBatlle->addChild(e);
		}
		if (name.find("H") != std::string::npos)
		{
			auto e = (Heli*)Heli::create(this);
			e->setPosition(eSpawnPoint);
			e->setMoveDirection(MOVE_NORTH);
			listEnemy.push_back(e);
			layerBatlle->addChild(e);
		}
		if (name.find("U") != std::string::npos)
		{
			auto e = (Ufo*)Ufo::create(this);
			e->setPosition(eSpawnPoint);
			e->setMoveDirection(MOVE_NORTH);
			listEnemy.push_back(e);
			layerBatlle->addChild(e);
		}
		//e->move();
	}
}

void BattleScene::setColliderToObjectlayer(TMXLayer* layer, int collisionBitmask)
{
	for (int i = 0; i < layer->getLayerSize().height; i++)
	{
		for (int j = 0; j < layer->getLayerSize().width; j++)
		{

			auto objID = layer->getTileGIDAt(Point(j, i));
			if (objID != 0)
			{
				auto obj = layer->getTileAt(Point(j, i));
				auto _physicsBody = PhysicsBody::createBox(obj->getContentSize());
				_physicsBody->setCollisionBitmask(collisionBitmask);
				_physicsBody->setGravityEnable(false);
				_physicsBody->setDynamic(false);
				_physicsBody->setContactTestBitmask(true);
				obj->setPhysicsBody(_physicsBody);
				if (collisionBitmask == ITEM_COLLISION_BITMASK)
				{
					obj->setScale(0.8);
					obj->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
					obj->setPosition(Point(obj->getPositionX()+tileMap->getTileSize().width/1.3 , obj->getPositionY() + tileMap->getTileSize().height/1.3 ));
				}
			}

		}
	}
}

void BattleScene::addColliderToTileMap()
{
	setColliderToObjectlayer(layerContainer, CONTAINER_COLLISION_BITMASK);
	setColliderToObjectlayer(layerObstacle, WALL_COLLISION_BITMASK);
	setColliderToObjectlayer(layerFrame, WALL_COLLISION_BITMASK);
	setColliderToObjectlayer(layerItem, ITEM_COLLISION_BITMASK);
}

void BattleScene::getTileMapComponents()
{
	layerground = tileMap->layerNamed("Ground");
	layerFrame = tileMap->getLayer("Frame");
	layerContainer = tileMap->getLayer("Containers");
	layerObstacle = tileMap->getLayer("Obstacles");
	entryPoints = tileMap->getObjectGroup("EntryPoints");
	layerItem = tileMap->getLayer("LayerItem");
}

Point BattleScene::tileCoordForPosition(Point point)
{
	int x = point.x / tileMap->getTileSize().width/tileMapScaled;
	int y = ((tileMap->getMapSize().height * tileMap->getTileSize().height) - (point.y/tileMapScaled)) / tileMap->getTileSize().height;
	return ccp(x, y);
}

Point BattleScene::positionForTileCoord(Point point)
{
	int x = point.x * tileMap->getTileSize().width * tileMapScaled;
	int y = ((tileMap->getMapSize().height * tileMap->getTileSize().height) -  point.y* tileMap->getTileSize().height)* tileMapScaled;
	return ccp(x, y);
}

bool BattleScene::detectCollision(Point point)
{
	Point tileCoord = tileCoordForPosition(point);
	auto objIDF = layerFrame->getTileGIDAt(Point((int)tileCoord.x, (int)tileCoord.y));
	auto objIDO = layerObstacle->getTileGIDAt(Point((int)tileCoord.x, (int)tileCoord.y));
	auto objIDC = layerContainer->getTileGIDAt(Point((int)tileCoord.x, (int)tileCoord.y));
	if (objIDF != 0 || objIDO != 0 || objIDC != 0)
	{
		return true;
	}

	
	return false;
}

TMXTiledMap* BattleScene::getTileMap()
{
	return this->tileMap;
}

CCTMXLayer* BattleScene::getLayerground()
{
	return this->layerground;
}

TMXLayer* BattleScene::getLayerFrame()
{
	return this->layerFrame;
}

TMXLayer* BattleScene::getLayerObstacle()
{
	return this->layerObstacle;
}

TMXLayer* BattleScene::getLayerContainer()
{
	return this->layerContainer;
}

CCTMXObjectGroup* BattleScene::getEntryPoints()
{
	return this->entryPoints;
}



void BattleScene::setPhysicsWorld(PhysicsWorld* physicsWorld)
{
	scenePhysicsWorld = physicsWorld;
}

