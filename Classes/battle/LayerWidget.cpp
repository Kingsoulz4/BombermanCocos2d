#include "LayerWidget.h"

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

	joyStick = Sprite::create("Controllers/JoyStick.png");
	joyStick->setPosition(Point(joyStick->getContentSize().width*2, joyStick->getContentSize().height*2));
	this->addChild(joyStick, 1);

	joyStickThumbnail = Sprite::create("Controllers/JoyStickThumb.png");
	joyStickThumbnail->setPosition(Point(joyStick->getContentSize().width * 2, joyStick->getContentSize().height * 2));
	joyStickThumbnail->setContentSize(joyStickThumbnail->getContentSize());
	joyStickThumbnail->setScale(1.5);
	joyStickThumbnail->setColor(Color3B::WHITE);
	this->addChild(joyStickThumbnail);

	auto touchListener = EventListenerTouchOneByOne::create();
	//touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(LayerWidget::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(LayerWidget::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(LayerWidget::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(LayerWidget::onTouchCancelled, this);


	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	
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
	playerUnderControl->move(cosA, sinA);
	
	
}

void LayerWidget::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
{
	joyStick->setPosition(joyStickDefaultPosition);
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

