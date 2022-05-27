#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class ChooseLevelScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();


    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(ChooseLevelScene);

};
