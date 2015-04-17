//
//  Player.cpp
//  DanmakuExorcism
//
//  Created by WanThirty on 14-7-24.
//
//

#include "Player.h"
#include "Bullet.h"
#include "GameLogic.h"

Player::Player()
{
    _playerType = PLAYER_DAOSHI;
    _HP = 0;
    _isShoot = true;
    _sp = nullptr;
    _hasInit = false;
    _aniIdle = nullptr;
    _aniSide = nullptr;
    _dir = DIR_UP;
}

Player::~Player()
{
    _aniIdle->release();
    _aniSide->release();
}

bool Player::init()
{
    if (BulletGenerator::init())
    {
        initialize();
        return true;
    }
    return false;
}

void Player::initialize()
{
    setBulletGeneratorType(BulletGeneratorType::PLAYER);
    for (int i = 0; i < 20; ++i) {
        Bullet* playerBlt = Bullet::create();
        BulletInfo bi;
        GameLogic::defaultBltInfo(bi);
        bi.BulletID = BULLET_DAOSHI_A;
        bi.v = 2000;
        bi.a = 90;
        playerBlt->setBulletInfo(bi);
        playerBlt->bulletDisable();
        GameLogic::addPlayerBullet(playerBlt);
    }
    schedule(schedule_selector(Player::updateBullets), 0.05f);
}

// public :

void Player::setPlayerInfo(PlayerType type, int hp)
{
    // set type
    _playerType = type;
    _HP = hp;
    
    // set texture by type
    std::string strFileName = "";
    if (type == PLAYER_DAOSHI)
    {
        strFileName = "playertest.png";
    }
    else if (type == PLAYER_HESHANG)
    {
        strFileName = "playertest.png";
    }
    else if (type == PLAYER_JIANKE)
    {
        strFileName = "playertest.png";
    }
    if (!_hasInit) {
        _hasInit = true;
        _sp = Sprite::create(strFileName);
        
        SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
        frameCache->addSpriteFramesWithFile("players/daoshi/daoshi.plist");
        
        _aniIdle = Animation::create();
        for (int i = 0; i < 3; ++i) {
            std::ostringstream nameStream;
            nameStream << "n_" << i << ".png";
            SpriteFrame* frame = frameCache->getSpriteFrameByName(nameStream.str().c_str());
            _aniIdle->addSpriteFrame(frame);
        }
        SpriteFrame* frame = frameCache->getSpriteFrameByName("n_1.png");
        _aniIdle->addSpriteFrame(frame);
        _aniIdle->setDelayPerUnit(0.1f);
        _aniIdle->setLoops(-1);
        _aniIdle->retain();
        
        _aniSide = Animation::create();
        for (int i = 0; i < 3; ++i) {
            std::ostringstream nameStream;
            nameStream << "s_" << i << ".png";
            SpriteFrame* frame = frameCache->getSpriteFrameByName(nameStream.str().c_str());
            _aniSide->addSpriteFrame(frame);
        }
        SpriteFrame* frame1 = frameCache->getSpriteFrameByName("s_1.png");
        _aniSide->addSpriteFrame(frame1);
        _aniSide->setDelayPerUnit(0.1f);
        _aniSide->setLoops(-1);
        _aniSide->retain();
        
        _sp->runAction(Animate::create(_aniIdle));
        
        this->addChild(_sp, 0);
    } else {
        _sp->setTexture(strFileName);
    }
    
    this->setContentSize(_sp->getContentSize());
    
    DanmakuPool::getInstance()->push(this);
}

void Player::setContainerSize(cocos2d::Size s)
{
    _containerSize = s;
}

void Player::shoot(bool isShoot)
{
    _isShoot = isShoot;
}

void Player::move(cocos2d::Touch *touch)
{
    auto posMoveOffset = touch->getLocation() - touch->getPreviousLocation();
    // player move by finger
    this->setPosition(this->getPosition() + posMoveOffset);// / this->getScale()
    if (posMoveOffset.x > 0) {
        moveAnimate(DIR_RIGHT);
    } else if (posMoveOffset.x < 0) {
        moveAnimate(DIR_LEFT);
    }
    
    // player should in screen
    if (this->getPositionX() - _sp->getContentSize().width / 2 < 0)
    {
        this->setPositionX(_sp->getContentSize().width / 2);
    }
    if (this->getPositionX() + _sp->getContentSize().width / 2 > _containerSize.width)
    {
        this->setPositionX(_containerSize.width - _sp->getContentSize().width / 2);
    }
    if (this->getPositionY() - _sp->getContentSize().height / 2 < 0)
    {
        this->setPositionY(_sp->getContentSize().height / 2);
    }
    if (this->getPositionY() + _sp->getContentSize().height > _containerSize.height)
    {
        this->setPositionY(_containerSize.height - _sp->getContentSize().height / 2);
    }
}

void Player::idle()
{
    moveAnimate(DIR_NONE);
}

// private :

void Player::updateBullets(float dt)
{
    if (_isShoot) {
        for (int i = 0; i < 2; ++i) {
            Bullet* blt = (Bullet*)DanmakuPool::getInstance()->getPlayerBullet();
            blt->setPosition(this->getPosition() + Vec2(i * 20 -10, 0));
            blt->setBulletID(BULLET_DAOSHI_A);
            blt->setVelocity(2000);
            blt->setAngle(90);
            blt->resetInfo();
            blt->bulletEnable();
        }
    }
}

void Player::moveAnimate(Direction dir)
{
    if (dir == _dir) {
        return;
    }
    _sp->stopAllActions();
    _dir = dir;
    
    Animate* a = nullptr;
    if (dir == DIR_LEFT) {
        a = Animate::create(_aniSide);
        _sp->setFlippedX(true);
    } else if (dir == DIR_RIGHT) {
        a = Animate::create(_aniSide);
        _sp->setFlippedX(false);
    } else {
        a = Animate::create(_aniIdle);
        _sp->setFlippedX(false);
    }
    _sp->runAction(a);
}





