#include "LayerWidget.h"
#include "ai/AIHigh.h"


Point joyStickDefaultPosition;

LayerWidget::LayerWidget()
{
}

LayerWidget::~LayerWidget()
{
}

bool LayerWidget::init()
{
	if (!Layer::init())
	{
		return false;
	}
	

	/*auto mainMenu = CSLoader::getInstance()->createNode("csb/LayerWidget.csb");
	this->addChild(mainMenu);
	mainMenu->setContentSize(this->getContentSize());*/

	auto visibleSize = Director::getInstance()->getVisibleSize();

	joyStick = Sprite::create("Controllers/JoyStick.png");
	joyStick->setPosition(Point(joyStick->getContentSize().width*2.5, joyStick->getContentSize().height*2.5));
	this->addChild(joyStick, 1);

	joyStickThumbnail = Sprite::create("Controllers/JoyStickThumb.png");
	joyStickThumbnail->setPosition(Point(joyStick->getContentSize().width * 2.5, joyStick->getContentSize().height * 2.5));
	joyStickThumbnail->setContentSize(joyStickThumbnail->getContentSize());
	joyStickThumbnail->setScale(1.5);
	joyStickThumbnail->setColor(Color3B::WHITE);
	this->addChild(joyStickThumbnail);

	auto touchListener = EventListenerTouchOneByOne::create();
	//auto touchListener = EventListenerTouchAllAtOnce::create();
	//touchListener->
	//touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(LayerWidget::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(LayerWidget::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(LayerWidget::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(LayerWidget::onTouchCancelled, this);


	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


	//add Controll button
	auto btnUseWeapon = ui::Button::create("Controllers/btnUseWeapon.png");
	btnUseWeapon->setPosition(Point(visibleSize.width-5*btnUseWeapon->getContentSize().width,  5*btnUseWeapon->getContentSize().height));
	this->addChild(btnUseWeapon);
	btnUseWeapon->setScale(5);
	btnUseWeapon->addClickEventListener([=](Ref*) {
		if (bombPlaced.size() < playerUnderControl->getBombLimit())
		{
			playerUnderControl->useWeapon();
			auto bomb = Bomb::create();
			bomb->setTag(BOMB_COLLISION_BITMASK);
			bomb->setPosition(Point(playerUnderControl->getPositionX(), playerUnderControl->getPositionY()));
			bombPlaced.push_back(bomb);
			battleScene->layerBatlle->addChild(bomb);
		}
		
	});

	auto btnPause = ui::Button::create("Controllers/btnUseWeapon.png");
	btnPause->setPosition(Point(visibleSize.width - 5 * btnPause->getContentSize().width, visibleSize.height - 5 * btnPause->getContentSize().height));
	this->addChild(btnPause);
	btnPause->setScale(5);
	btnPause->addClickEventListener([=](Ref*) {
		battleScene->changeEnemyDirection();
	});

	//Update
	this->scheduleUpdate();
	return true;
}

void LayerWidget::setPlayerUnderControl(Bomber* bomber)
{
	playerUnderControl = bomber;
}

Bomber * LayerWidget::getPlayerUnderControl()
{
	return this->playerUnderControl;
}

LayerWidget* LayerWidget::create(BattleScene* battleScene)
{
	auto ret = new (std::nothrow) LayerWidget;
	if (ret && ret->init()) {
		ret->autorelease();
		ret->battleScene = battleScene;
		return ret;
	}
	CC_SAFE_RELEASE(ret);
	return nullptr;
}

bool LayerWidget::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	joyStickDefaultPosition = joyStick->getPosition();
	return true;
}

void LayerWidget::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event)
{
	
	Point position = Director::getInstance()->convertToGL(touch->getLocationInView());
	position = this->convertToNodeSpace(position);
	double distanceFromOriginPos = distanceRadiusJoyStick(position);
	double cosA = (position.x - joyStickDefaultPosition.x) / distanceFromOriginPos;
	double sinA = (position.y - joyStickDefaultPosition.y) / distanceFromOriginPos;
	if (distanceFromOriginPos > joyStickThumbnail->getContentSize().height)
	{
		double radius = joyStickThumbnail->getContentSize().height ;
		position.x = radius * cosA + joyStickDefaultPosition.x;
		position.y = radius * sinA + joyStickDefaultPosition.y;
	}
	joyStick->setPosition(position);
	auto delta = DelayTime::create(0.001f);
	
	if (getDirection(cosA, sinA) != playerUnderControl->getMoveDirection())
	{
		this->stopActionByTag(PLAYER_MOVE_ACTION);
		auto playerMoveSequence = RepeatForever::create(Sequence::create(delta, CallFunc::create([=] {
			playerUnderControl->move(cosA, sinA);
			
			}), 
			CallFunc::create([=] {
				AudioManger::getInstance()->playBomberWalk();

			}), NULL));
		playerMoveSequence->setTag(PLAYER_MOVE_ACTION);
		this->runAction(playerMoveSequence);
	}
	
	//playerUnderControl->move(cosA, sinA);
	
	
}

void LayerWidget::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
{
	this->stopActionByTag(PLAYER_MOVE_ACTION);
	joyStick->setPosition(joyStickDefaultPosition);
	playerUnderControl->setMoveDirection(0);
}

void LayerWidget::onTouchCancelled(cocos2d::Touch * touch, cocos2d::Event * event)
{
	joyStick->setPosition(joyStickDefaultPosition);
	playerUnderControl->stopAllActions();
}

double LayerWidget::distanceRadiusJoyStick(Point destination)
{
	double dis = sqrt(pow(joyStickDefaultPosition.x - destination.x, 2) + pow(joyStickDefaultPosition.y - destination.y, 2));
	return dis;
}

void LayerWidget::update(float dt)
{
	//update bomb
	auto ptr = bombPlaced.begin();
	while (ptr < bombPlaced.end())
	{
		if (( * ptr)->getTimeExplode() <= 0.f)
		{
			
			auto flames = Flames::create(battleScene->getBomber()->getFlamePower());
			//auto flames = Flames::create();
			battleScene->layerBatlle->addChild(flames);
			flames->setPosition((*ptr)->getPosition());
			flamesBurning.push_back(flames);
			battleScene->layerBatlle->removeChild(*ptr);
			bombPlaced.erase(ptr);
			AudioManger::getInstance()->playBombExplode();
			break;
		}
		else
		{
			ptr++;
		}
	}
	//update flames
		auto flame = flamesBurning.begin();
		while (flame < flamesBurning.end())
		{
			if ((*flame)->getTimeDouse() <= 0.f)
			{
				battleScene->layerBatlle->removeChild((*flame));
				flamesBurning.erase(flame);
				//delete((*flame));
				break;
			}
			else
			{
				flame++;
			}
		}
	
	
	
}

