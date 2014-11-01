#include "GamingScene.h"
#include "GamingLayer.h"
#include "LayerManager.h"
#include "DataAdapter.h"

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
    this->addChild(LayerManager::getInstance());
    DataAdapter::getInstance()->LoadStageList();
    DataAdapter::getInstance()->LoadEnemyList(1);
    GamingLayer* layer = GamingLayer::create();
    LayerManager::getInstance()->pushLayer(layer);
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
