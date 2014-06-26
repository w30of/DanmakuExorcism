#include "GamingScene.h"
#include "GamingLayer.h"

Scene* GamingScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GamingScene::create();
    scene->addChild(layer);
    return scene;
}

bool GamingScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    GamePreparing();
    return true;
}

void GamingScene::GamePreparing()
{
    GamingLayer* layer = GamingLayer::create();
    this->addChild(layer);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    if (visibleSize.width / visibleSize.height > layer->getContentSize().width / layer->getContentSize().height)
    {
        layer->setScale(visibleSize.height / layer->getContentSize().height);
    } else {
        layer->setScale(visibleSize.width / layer->getContentSize().width);
    }
    
    layer->setPosition(0, (visibleSize.height - layer->getContentSize().height) / 2);
}

void GamingScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
