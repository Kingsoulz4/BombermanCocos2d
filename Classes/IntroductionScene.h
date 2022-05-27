#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class IntroductionScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    void addControllers();

    virtual bool init();
    void update(float dt);
    float _loadingTime = 5.f;

    // implement the "static create()" method manually
    CREATE_FUNC(IntroductionScene);
   
};
