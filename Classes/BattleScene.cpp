#include "BattleScene.h"
#include "battle/LayerWidget.h"



bool BattleScene::init()
{
	if (!Scene::create())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleSize();

	tileMap = new CCTMXTiledMap();
	tileMap->initWithTMXFile("tmx/battle1.tmx");
	tileMap->setScale(1.5);
	tileMap->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	tileMap->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	
	player = (Bomber*)Bomber::create("Sprites/Player/BomberWalkDown1.png");
	
	player->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
	
	this->addChild(tileMap);
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
	meta = tileMap->layerNamed("Meta");
	meta->setVisible(false);

	return true;
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
	int y = 
	return CCPoint();
}
