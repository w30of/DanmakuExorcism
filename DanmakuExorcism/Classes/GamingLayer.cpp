//
//  GamingLayer.cpp
//  DanmakuExorcism
//
//  Created by WanThirty on 14-6-25.
//
//

#include "GamingLayer.h"
#include "LayerManager.h"
#include "GameLogic.h"

GamingLayer::GamingLayer()
{
    _player = nullptr;
    m_time = 0.0f;
}

GamingLayer::~GamingLayer()
{
    
}

bool GamingLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    prepare();
    return true;
}

void GamingLayer::prepare()
{
    GameLogic::getInstance()->gLayer = this;
    
// preset layer status
    this->setContentSize(Size(640, 960));
    this->setAnchorPoint(Point::ZERO);
    m_WinSize = this->getContentSize();
    GameLogic::getInstance()->winSize = m_WinSize;
    GameLogic::setGameRect(Rect(0, 0, m_WinSize.width, m_WinSize.height));
    
    // touch listener
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GamingLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GamingLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GamingLayer::onTouchEnded, this);
    
    // set priority
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
// let the game go
    this->scheduleUpdate();
    
    // to show the time flow
    auto lbTime = Label::createWithSystemFont("test", "Helvetica-Bold", 22);
    this->addChild(lbTime);
    lbTime->setTag(9);
    lbTime->setPosition(m_WinSize.width - 60, m_WinSize.height - 30);
    
    // background
    auto sprBg1 = Sprite::create("background.png");
    sprBg1->setAnchorPoint(Point::ZERO);
    sprBg1->setPosition(Point::ZERO);
    sprBg1->setScale(2);
    sprBg1->setTag(7);
    this->addChild(sprBg1);
    
    auto sprBg2 = Sprite::create("background.png");
    sprBg2->setAnchorPoint(Point::ZERO);
    sprBg2->setPosition(0, m_WinSize.height);
    sprBg2->setScale(2);
    sprBg2->setTag(8);
    this->addChild(sprBg2);
}

// show the palyer
void GamingLayer::setPlayerType(PlayerType type)
{
    if (type == PLAYER_DAOSHI) {
        _player = Player::create();
        this->addChild(_player, ZORDER_PLAYER);
        _player->setPlayerInfo(PLAYER_DAOSHI, 10);
        _player->setPosition(m_WinSize.width / 2, - _player->getContentSize().height / 2);
        _player->runAction(Sequence::create(EaseExponentialOut::create(MoveTo::create(0.6f, Vec2(m_WinSize.width / 2, m_WinSize.height / 5))), NULL));
        _player->setContainerSize(this->getContentSize());
        
        GameLogic::getInstance()->gPlayer = _player;
    }
}

void GamingLayer::update(float dt)
{
    // show the label of time
    m_time += dt;
    auto lbtime = (Label*)getChildByTag(9);
    lbtime->setString(String::createWithFormat("%.2f", m_time)->getCString());
    
    // background move
    Sprite* bg1 = (Sprite*)getChildByTag(7);
    Sprite* bg2 = (Sprite*)getChildByTag(8);
    GameLogic::getInstance()->autoMove(bg1, bg2, -100*dt);
    
    // create enemy by time
    GameLogic::getInstance()->createEnemy(m_time);
}

bool GamingLayer::onTouchBegan(Touch* touch, Event  *event)
{
    if (!_player) return false;
    _player->shoot(true);
    return true;
}

void GamingLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (!_player) return;
    
    _player->move(touch);
}

void GamingLayer::onTouchEnded(Touch* touch, Event  *event)
{
    if (!_player) return;
    _player->shoot(false);
}















