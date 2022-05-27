#include "ChooseLevelScene.h"
#include "BattleScene.h"
#include "IntroductionScene.h"

cocos2d::Scene* ChooseLevelScene::createScene()
{
    return ChooseLevelScene::create();
}

bool ChooseLevelScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();

	/*auto background = Sprite::create("backgrounds/character-selection-background.jpg");
	this->addChild(background);
	background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	background->setScaleX(1.2);
	background->setScaleY(0.7);

	auto btnPlay = ui::Button::create("Controllers/Play.png");
	btnPlay->addClickEventListener([=](Ref*) {
		Director::getInstance()->replaceScene(TransitionFade::create(1.2f, BattleScene::createScene(1)));
		});
	this->addChild(btnPlay);
	btnPlay->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));

	auto btnReturn = ui::Button::create("Controllers/Play.png");
	btnReturn->addClickEventListener([=](Ref*) {
		Director::getInstance()->replaceScene(TransitionFade::create(1.2f, IntroductionScene::createScene()));
		});
	this->addChild(btnReturn);
	btnReturn->setPosition(Point(btnReturn->getContentSize().width, visibleSize.height - btnReturn->getContentSize().height));


	auto txtLevel = ui::TextField::create();
	txtLevel->setText("Aaaaa");
	txtLevel->setInsertText(true);
	txtLevel->
	txtLevel->setPosition(Point(visibleSize.width/3, visibleSize.height/3));
	this->addChild(txtLevel);*/


	auto mainLayer = CSLoader::getInstance()->createNode("csb/LayerChooseLevel.csb");
	this->addChild(mainLayer);
	auto txtLevel = mainLayer->getChildByName<ui::TextField*>("txtLevel");
	txtLevel->setCursorEnabled(true);
	
	auto btnPlay = mainLayer->getChildByName<ui::Button*>("btnPlay");
	btnPlay->addClickEventListener([=](Ref*) {
		std::string level = txtLevel->getString();
		Director::getInstance()->replaceScene(TransitionFade::create(1.2f, BattleScene::createScene(std::stoi(level))));
	});

	auto btnReturn = mainLayer->getChildByName<ui::Button*>("btnReturn");
	btnReturn->addClickEventListener([=](Ref*) {
		Director::getInstance()->replaceScene(TransitionFade::create(1.2f, IntroductionScene::createScene()));
	});
	return true;
}
