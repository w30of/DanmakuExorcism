#include "HelloWorldScene.h"

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    GamePreparing();
    return true;
}

void HelloWorld::GamePreparing()
{
    m_WinSize = Director::getInstance()->getVisibleSize();
    
    auto sprite = Sprite::create("HelloWorld.png");
    
    sprite->setPosition(Vec2(m_WinSize.width/2, m_WinSize.height/2));
    // to show the border of visible size
    sprite->setScale(m_WinSize.width / sprite->getContentSize().width, 1);
    
    this->addChild(sprite, 0);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
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
