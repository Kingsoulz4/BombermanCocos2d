#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "audio/AudioManager.h"


USING_NS_CC;

class OptionScene : public cocos2d::Scene
{
public:
    virtual bool init();

    void update(float dt);

    // implement the "static create()" method manually
    CREATE_FUNC(OptionScene);

};
