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
    m_WinSize = this->getContentSize();
    this->setAnchorPoint(Point::ZERO);
    
    GameLogic::getInstance()->winSize = m_WinSize;
    
    // touch listener
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GamingLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GamingLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GamingLayer::onTouchEnded, this);
    
    // set priority
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
// let the game go
    this->scheduleUpdate();
    
    // show the palyer
    _player = Player::create();
    this->addChild(_player, ZORDER_PLAYER);
    _player->setPlayerInfo(PLAYER_DAOSHI, 10);
    _player->setPosition(m_WinSize.width / 2, - _player->getContentSize().height / 2);
    _player->runAction(Sequence::create(EaseExponentialOut::create(MoveTo::create(0.6f, Vec2(m_WinSize.width / 2, m_WinSize.height / 5))), NULL));
    
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

void GamingLayer::update(float dt)
{
    // show the label of time
    m_time += dt;
    auto lbtime = (Label*)getChildByTag(9);
    lbtime->setString(String::createWithFormat("%.2f", m_time)->getCString());
    
    // background move
    Sprite* bg1 = (Sprite*)getChildByTag(7);
    if (bg1) {
        bg1->setPositionY(bg1->getPositionY() - 100*dt);
        if (bg1->getPositionY() < -m_WinSize.height) {
            bg1->setPositionY(m_WinSize.height);
        }
    }
    Sprite* bg2 = (Sprite*)getChildByTag(8);
    if (bg2) {
        bg2->setPositionY(bg2->getPositionY() - 100*dt);
        if (bg2->getPositionY() < -m_WinSize.height) {
            bg2->setPositionY(m_WinSize.height);
        }
    }
    
    // create stage info
}

bool GamingLayer::onTouchBegan(Touch* touch, Event  *event)
{
    _player->shoot(true);
    return true;
}

void GamingLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    auto posMoveOffset = touch->getLocation() - touch->getPreviousLocation();
    if (_player) {
        // player move by finger
        _player->setPosition(_player->getPosition() + posMoveOffset / this->getScale());
        
        // player should in screen
        if (_player->getPositionX() - _player->getContentSize().width / 2 < 0)
        {
            _player->setPositionX(_player->getContentSize().width / 2);
        }
        if (_player->getPositionX() + _player->getContentSize().width / 2 > m_WinSize.width)
        {
            _player->setPositionX(m_WinSize.width - _player->getContentSize().width / 2);
        }
        if (_player->getPositionY() - _player->getContentSize().height / 2 < 0)
        {
            _player->setPositionY(_player->getContentSize().height / 2);
        }
        if (_player->getPositionY() + _player->getContentSize().height > m_WinSize.height)
        {
            _player->setPositionY(m_WinSize.height - _player->getContentSize().height / 2);
        }
    }
}

void GamingLayer::onTouchEnded(Touch* touch, Event  *event)
{
    _player->shoot(false);
    auto location = touch->getLocation();
}















