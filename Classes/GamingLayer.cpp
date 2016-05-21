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
    this->setContentSize(Director::getInstance()->getVisibleSize());
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
    auto sprBg1 = Sprite::create("texture/background.png");
    sprBg1->setAnchorPoint(Point::ZERO);
    sprBg1->setPosition(Point::ZERO);
    sprBg1->setScale(2);
    sprBg1->setTag(7);
    this->addChild(sprBg1);
    
    auto sprBg2 = Sprite::create("texture/background.png");
    sprBg2->setAnchorPoint(Point::ZERO);
    sprBg2->setPosition(0, m_WinSize.height);
    sprBg2->setScale(2);
    sprBg2->setTag(8);
    this->addChild(sprBg2);
    
    GameLogic::getInstance()->resetPlay();
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

void GamingLayer::showLogo(int stageID)
{
    if (stageID == 1) {
        Sprite* sprLogo = Sprite::create("texture/stage1/logo_stage1.png");
        this->addChild(sprLogo, 999, 999);
        Size contentSize = this->getContentSize();
        sprLogo->setPosition(contentSize.width/2, contentSize.height/2);
        
//        auto fileUtiles = FileUtils::getInstance();
//        auto fragmentFullPath = fileUtiles->fullPathForFilename("example_Blur.fsh");
//        auto fragSource = fileUtiles->getStringFromFile(fragmentFullPath);
//        auto glprogram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
//        GLProgramState* _glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
//        _glprogramstate->retain();
//        _glprogramstate->setUniformVec2("resolution", sprLogo->getTexture()->getContentSizeInPixels());
//        _glprogramstate->setUniformFloat("blurRadius", 5.0f);
//        _glprogramstate->setUniformFloat("sampleNum", 5.0f);
//        sprLogo->setGLProgram(glprogram);
        
        sprLogo->setOpacity(0);
        sprLogo->runAction(Sequence::create(FadeIn::create(1),
                                            DelayTime::create(1),
                                            FadeOut::create(1),
                                            CallFunc::create([=](){sprLogo->removeFromParent();}),
                                            NULL));
    }
}

void GamingLayer::update(float dt)
{
    // show the label of time
    auto lbtime = (Label*)getChildByTag(9);
    lbtime->setString(StringUtils::format("%.2f", GameLogic::getInstance()->gamePlayTime));
    
    // background move
    Sprite* bg1 = (Sprite*)getChildByTag(7);
    Sprite* bg2 = (Sprite*)getChildByTag(8);
    GameLogic::getInstance()->autoMove(bg1, bg2, -100*dt);
    
    // create enemy by time
    GameLogic::getInstance()->createEnemy(dt);
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
    _player->idle();
}















