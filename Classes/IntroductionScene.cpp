#include "IntroductionScene.h"
#include "BattleScene.h"
#include "ChooseLevelScene.h"
#include "OptionScene.h"


ui::LoadingBar* progressBar;
ui::Text* txtLoading;

cocos2d::Scene* IntroductionScene::createScene()
{
	return IntroductionScene::create();
}

void IntroductionScene::addControllers()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	/*auto background = Sprite::create("backgrounds/menu-background.jpg");
	this->addChild(background);
	background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	background->setScaleX(1.2);*/

	auto btnPlay = ui::Button::create("Controllers/Play.png");
	btnPlay->addClickEventListener([=](Ref*) {
		AudioManger::getInstance()->stopIntroductionSound();
		AudioManger::getInstance()->playBomberPlaceBomb();
		Director::getInstance()->replaceScene(TransitionFade::create(1.2f, ChooseLevelScene::createScene()));
		});
	this->addChild(btnPlay);
	btnPlay->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));

	auto btnOption = ui::Button::create("Controllers/Option.png");
	btnOption->addClickEventListener([=](Ref*) {
		AudioManger::getInstance()->playBomberPlaceBomb();
		Director::getInstance()->replaceScene(TransitionFade::create(1.2f, OptionScene::create()));
		});
	this->addChild(btnOption);
	btnOption->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 - btnOption->getContentSize().height));

	auto btnHighScore = ui::Button::create("Controllers/HightScore.png");
	btnHighScore->addClickEventListener([=](Ref*) {
		AudioManger::getInstance()->playBomberPlaceBomb();
		});
	this->addChild(btnHighScore);
	btnHighScore->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 - 2 * btnOption->getContentSize().height));


	auto btnExit = ui::Button::create("Controllers/Exit.png");
	btnExit->addClickEventListener([=](Ref*) {
		AudioManger::getInstance()->playBomberPlaceBomb();
		exit(1);
		});
	this->addChild(btnExit);
	btnExit->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 - 3 * btnOption->getContentSize().height));
}



bool IntroductionScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto percent = 1;
	AudioManger::getInstance()->playIntroductionSound();
	auto mainLayer = CSLoader::getInstance()->createNode("csb/SplashScene.csb");
	this->addChild(mainLayer);

	progressBar = mainLayer->getChildByName<ui::LoadingBar*>("progressBar");
	progressBar->setPercent(percent);
	txtLoading = mainLayer->getChildByName<ui::Text*>("txtLoading");

	
	this->scheduleUpdate();


	

	return true;
}

void IntroductionScene::update(float dt)
{
	if (_loadingTime > 0)
	{
		_loadingTime -= dt;
		progressBar->setPercent(100 - ((_loadingTime) / 5) * 100);
		txtLoading->setString("Loading...  " + std::to_string((int)((((int)5.f - _loadingTime) / 5)*100)) + "%");
	}
	if (_loadingTime <0 )
	{
		progressBar->removeFromParent();
		txtLoading->removeFromParent();
		addControllers();
		_loadingTime = 0;
	}

}
