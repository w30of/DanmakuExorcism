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
}

Player::~Player()
{
    
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
//        playerBlt->setBulletInfo(BULLET_DAOSHI_A, 90, 2000);
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





