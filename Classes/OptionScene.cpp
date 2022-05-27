#include "OptionScene.h"
#include "IntroductionScene.h"

ui::CheckBox* checkBoxMusic;
ui::CheckBox* checkBoxEffect;
bool OptionScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto mainLayer = CSLoader::getInstance()->createNode("csb/OptionScene.csb");
	this->addChild(mainLayer);

	checkBoxMusic = mainLayer->getChildByName<ui::CheckBox*>("checkBoxMusic");
	checkBoxEffect = mainLayer->getChildByName<ui::CheckBox*>("checkBoxEffect");

	auto btnReturn = mainLayer->getChildByName<ui::Button*>("btnReturn");
	btnReturn->addClickEventListener([=](Ref*) {
		Director::getInstance()->replaceScene(TransitionFade::create(1.2f, IntroductionScene::createScene()));
	});

	

	checkBoxMusic->addClickEventListener([=](Ref*) {
		if (checkBoxMusic->getSelectedState())
		{
			AudioManger::getInstance()->disableMusic();
		}
		else
		{
			AudioManger::getInstance()->enableMusic();
		}
		
	});

	checkBoxEffect->addClickEventListener([=](Ref*) {
		if(checkBoxEffect->isSelected())
		{
			AudioManger::getInstance()->disableAllEffects();
		}
		else
		{
			AudioManger::getInstance()->enableAllEffects();
		}

		});

	this->scheduleUpdate();
	

    return true;
}

void OptionScene::update(float dt)
{
	

	
}
